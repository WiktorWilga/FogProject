// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpellsHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FOG_API USpellsHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UImage* UpSlot;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UImage* CentralSlot;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UImage* DownSlot;

	TArray<class UTexture2D*> SpellsIcons;
	uint8 CurrentSpellIcon = 0;

	void RefreshIcons();
	void ClearIcons();

public:

	void SetSpells(TArray<class UTexture2D*> InSpellsIcons);

	void NextSpell();
	void PreviousSpell();

	uint8 GetShiftedIndex(int8 Offset);

};
