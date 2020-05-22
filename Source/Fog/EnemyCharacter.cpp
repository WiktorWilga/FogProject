// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Weapon.h"
#include "WeaponStructures.h"
#include "FogCharacter.h"
#include "EnemyController.h"
#include "BrainComponent.h"
#include "Animation/AnimMontage.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetVisibility(true);
	HealthWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	OffsetLocation = GetActorLocation();

	SetupEnemyWeapon();

	HealthWidget->SetWidgetClass(HealthWidgetClass);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AEnemyCharacter::GetNextTargetLocation()
{
	++CurrentTargetLocation;
	CurrentTargetLocation %= TargetLocations.Num();

	return (TargetLocations[CurrentTargetLocation] + OffsetLocation);
}

void AEnemyCharacter::SetupEnemyWeapon()
{
	AWeapon* MyWeapon = Cast<AWeapon>(WeaponComponent->GetChildActor());
	if (MyWeapon && !WeaponRef.IsNull())
	{
		FString Context;
		MyWeapon->SetWeaponData(WeaponRef.GetRow<FWeaponInfo>(Context));
	}
}

bool AEnemyCharacter::IsEnemy(AFightCharacter* Character)
{
	return Character->IsA<AFogCharacter>();
}

void AEnemyCharacter::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
						AActor* DamageCauser)
{
	AEnemyController* MyController = Cast<AEnemyController>(Controller);

	if (TakeDamageReactionAnim && MyController)
	{
		float AnimTime = TakeDamageReactionAnim->GetPlayLength() / TakeDamageReactionAnim->RateScale;
		MyController->SetTakeDamageReactionForTime(AnimTime);
		NetMulticast_PlayMontage(TakeDamageReactionAnim);
	}
	
	Super::TakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	NetMulticast_RefreshHealthBar(Health / MaxHealth);
}

void AEnemyCharacter::NetMulticast_RefreshHealthBar_Implementation(float Percent)
{
	UHealthBarWidget* HealthBar = Cast<UHealthBarWidget>(HealthWidget->GetUserWidgetObject());
	if (HealthBar)
	{
		HealthBar->SetHealthPercent(Percent);

		if (Percent <= 0.0f)
		{
			HealthWidget->SetVisibility(false);
		}
		else //for situation when smt goes wrong and for moment client hasn't got true info
		{
			HealthWidget->SetVisibility(true);
		}
	}
}
