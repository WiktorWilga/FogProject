// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FogPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "FogCharacter.h"
#include "Engine/World.h"
#include "InventoryMenuElementWidget.h"
#include "GameFramework/PawnMovementComponent.h"

AFogPlayerController::AFogPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	SetReplicates(true);
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
