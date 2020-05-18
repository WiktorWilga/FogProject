// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FogPlayerController.generated.h"

UCLASS()
class AFogPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFogPlayerController();

	void BeginPlay() override;

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	// Player input
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void OnInteract();
	UFUNCTION()
		void OnAttack();

	UFUNCTION()
		void Dodge();

	UFUNCTION()
		void OnNextSpell();
	UFUNCTION()
		void OnPreviousSpell();
	UFUNCTION()
		void OnUseSpell();

	/**Inventory menu*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UInventoryMenuWidget> InventoryMenuClass;
	UPROPERTY()
		class UInventoryMenuWidget* InventoryMenuInstance;
	void CreateInventoryMenu();
	UFUNCTION()
		void OnInventory();
	/****************/

	/**HUD*/
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UFogHUDWidget> HUDClass;
	UPROPERTY()
		class UFogHUDWidget* HUDInstance;
	void CreateHUD();
	void SetHUDSpellsIcons(TArray<class UTexture2D*> InSpellsIcons);
	/******/

};


