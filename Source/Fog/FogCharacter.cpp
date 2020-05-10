// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FogCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractableObject.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/DataTable.h"
#include "Components/ChildActorComponent.h"
#include "Weapon.h"
#include "EnemyCharacter.h"

AFogCharacter::AFogCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion()); 

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SetReplicates(true);
	SetReplicateMovement(true);
}

void AFogCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFogCharacter, Inventory);
}

void AFogCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocallyControlled())
	{
		CursorToWorld->SetVisibility(false);
	}
	else if (CursorMaterialInstance)
	{
		CursorMaterial = UMaterialInstanceDynamic::Create(CursorMaterialInstance, nullptr);
		CursorToWorld->SetDecalMaterial(CursorMaterial);
	}
}

void AFogCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (IsLocallyControlled())
	{
		CursorTick();
		RotateCharacterToCursor(DeltaSeconds);
	}
}

void AFogCharacter::CursorTick()
{
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CursorToWorld == nullptr || PC == nullptr) return;

	FHitResult TraceHitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	CursorToWorld->SetWorldLocation(TraceHitResult.Location);
}

void AFogCharacter::RotateCharacterToCursor(float DeltaSeconds)
{
	if (CursorToWorld == nullptr) return;
	
	FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CursorToWorld->GetComponentLocation());
	DesiredRotation.Roll = DesiredRotation.Pitch = 0.0f;
	FRotator AllowedDeltaRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(), DesiredRotation, DeltaSeconds, 4.0f);
	
	//set in controller rotation, because character use controller yaw rotation, thanks to rotation is automaticly replicated
	//by movement component
	GetController<APlayerController>()->SetControlRotation(AllowedDeltaRotation);
	GetController<APlayerController>()->UpdateRotation(DeltaSeconds);
}

void AFogCharacter::AddPickUpObjectToInventory(FName PickUpName, uint32 Amount)
{
	int32 Result = GetInventoryItemIndex(PickUpName);
	if (Result != -1)
	{
		Inventory.RemoveAt(Result);
		Inventory.Add(FInventoryItemWithCounter(PickUpName, (Inventory[Result].Num + Amount)));
	}
	else
	{
		Inventory.Add(FInventoryItemWithCounter(PickUpName,  Amount));
	}
}

void AFogCharacter::RemovePickUpObjectFromInventory(FName PickUpName, uint32 Amount)
{
	int32 Result = GetInventoryItemIndex(PickUpName);
	if (Result != -1)
	{
		if (Amount >= Inventory[Result].Num)
		{
			Inventory.RemoveAt(Result);
		}
		else
		{
			Inventory.RemoveAt(Result);
			Inventory.Add(FInventoryItemWithCounter(PickUpName, (Inventory[Result].Num - Amount)));
		}
	}
}

int32 AFogCharacter::GetInventoryItemIndex(FName Name)
{
	for (int32 i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i].Name.IsEqual(Name))
		{
			return i;
		}
	}

	return -1;
}

void AFogCharacter::Server_MakeCurrentInteraction_Implementation()
{
	if (Server_AvaliableInteraction)
	{
		Server_AvaliableInteraction->Interact(this);
		Server_AvaliableInteraction = nullptr;
	}
}

FWeaponInfo* AFogCharacter::GetWeapon()
{
	if (!WeaponComponent) return nullptr;

	AWeapon* MyWeapon = Cast<AWeapon>(WeaponComponent->GetChildActor());
	if (!MyWeapon) return nullptr;

	return MyWeapon->GetWeaponData();
}

void AFogCharacter::Server_SetWeapon_Implementation(FName WeaponName)
{
	if (!WeaponComponent) return;

	const FString Context;
	FWeaponInfo* ItemData = WeaponDataTable->FindRow<FWeaponInfo>(WeaponName, Context);
	if (!ItemData) return;

	AWeapon* MyWeapon = Cast<AWeapon>(WeaponComponent->GetChildActor());
	if (!MyWeapon) return;

	MyWeapon->SetWeaponData(ItemData);
}

bool AFogCharacter::Server_SetWeapon_Validate(FName WeaponName)
{
	return GetInventoryItemIndex(WeaponName) != -1;
}

bool AFogCharacter::IsEnemy(AFightCharacter* Character)
{
	return Character->IsA<AEnemyCharacter>();
}
