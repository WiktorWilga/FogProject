// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FogPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "FogCharacter.h"
#include "Engine/World.h"
#include "InventoryMenuWidget.h"
#include "GameFramework/PawnMovementComponent.h"
#include "FogHUDWidget.h"
#include "SpellsHUDWidget.h"


AFogPlayerController::AFogPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	SetReplicates(true);
}

void AFogPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		CreateHUD();
		HUDInstance->AddToViewport();
	}
}

void AFogPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AFogPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Interaction", IE_Pressed, this, &AFogPlayerController::OnInteract);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AFogPlayerController::OnAttack);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &AFogPlayerController::Dodge);
	InputComponent->BindAction("OpenInventory", IE_Pressed, this, &AFogPlayerController::OnInventory);
	InputComponent->BindAction("NextSpell", IE_Pressed, this, &AFogPlayerController::OnNextSpell);
	InputComponent->BindAction("PreviousSpell", IE_Pressed, this, &AFogPlayerController::OnPreviousSpell);

	InputComponent->BindAxis("Forward", this, &AFogPlayerController::MoveForward);
	InputComponent->BindAxis("Right", this, &AFogPlayerController::MoveRight);
}

void AFogPlayerController::MoveForward(float Value)
{
	if (!GetCharacter()) return;
	if (Value == 0.0f) return;

	FVector Direction(Value, 0.0f, 0.0f);
	GetCharacter()->GetMovementComponent()->AddInputVector(Direction);
}

void AFogPlayerController::MoveRight(float Value)
{
	if (!GetCharacter()) return;
	if (Value == 0.0f) return;

	FVector Direction(0.0f, Value, 0.0f);
	GetCharacter()->GetMovementComponent()->AddInputVector(Direction);
}

void AFogPlayerController::OnInteract()
{
	auto FogCharacter = Cast<AFogCharacter>(GetCharacter());
	if (!FogCharacter) return;

	FogCharacter->Server_MakeCurrentInteraction();
}

void AFogPlayerController::OnAttack()
{
	auto FogCharacter = Cast<AFogCharacter>(GetCharacter());
	if (!FogCharacter) return;

	FogCharacter->Server_PerformAttack();
}

void AFogPlayerController::Dodge()
{
	auto FogCharacter = Cast<AFogCharacter>(GetCharacter());
	if (!FogCharacter) return;

	FogCharacter->Server_StartDodge();
}

void AFogPlayerController::CreateInventoryMenu()
{
	if (!InventoryMenuClass) return;

	InventoryMenuInstance = CreateWidget<UInventoryMenuWidget>(this, InventoryMenuClass);
}

void AFogPlayerController::OnInventory()
{
	if (!InventoryMenuInstance)
	{
		CreateInventoryMenu();
	}
	
	if (InventoryMenuInstance->IsInViewport())
	{
		InventoryMenuInstance->RemoveFromParent();

		SetHUDSpellsIcons(InventoryMenuInstance->GetSelectedSpelssIcons());
	}
	else	
	{
		InventoryMenuInstance->AddToViewport();
	}
}

void AFogPlayerController::CreateHUD()
{
	if (!HUDClass) return;

	HUDInstance = CreateWidget<UFogHUDWidget>(this, HUDClass);
}

void AFogPlayerController::SetHUDSpellsIcons(TArray<UTexture2D*> InSpellsIcons)
{
	if(HUDInstance && HUDInstance->WBP_SpellsHUD)
	{
		HUDInstance->WBP_SpellsHUD->SetSpells(InSpellsIcons);
	}
}

void AFogPlayerController::OnNextSpell()
{
	if (HUDInstance && HUDInstance->WBP_SpellsHUD)
	{
		HUDInstance->WBP_SpellsHUD->NextSpell();
	}
}

void AFogPlayerController::OnPreviousSpell()
{
	if (HUDInstance && HUDInstance->WBP_SpellsHUD)
	{
		HUDInstance->WBP_SpellsHUD->PreviousSpell();
	}
}