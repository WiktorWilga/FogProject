// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellsHUDWidget.h"
#include "Components/Image.h"

void USpellsHUDWidget::SetSpells(TArray<UTexture2D*> InSpellsIcons)
{
	SpellsIcons = InSpellsIcons;
	RefreshIcons();
}

void USpellsHUDWidget::RefreshIcons()
{
	ClearIcons();

	if (!SpellsIcons.Num()) return;

	if (CurrentSpellIcon >= SpellsIcons.Num())
	{
		CurrentSpellIcon = SpellsIcons.Num() - 1;
	}

	uint8 UpIndex = GetShiftedIndex(1);
	uint8 Downindex = GetShiftedIndex(-1);

	UpSlot->SetBrushFromTexture(SpellsIcons[UpIndex]);
	CentralSlot->SetBrushFromTexture(SpellsIcons[CurrentSpellIcon]);
	DownSlot->SetBrushFromTexture(SpellsIcons[Downindex]);
}

void USpellsHUDWidget::ClearIcons()
{
	UpSlot->SetBrushFromMaterial(nullptr);
	CentralSlot->SetBrushFromMaterial(nullptr);
	DownSlot->SetBrushFromMaterial(nullptr);
}

uint8 USpellsHUDWidget::GetShiftedIndex(int8 Offset)
{
	int16 DesiredIndex = CurrentSpellIcon + Offset;

	if (DesiredIndex < 0)
	{
		DesiredIndex = SpellsIcons.Num() - 1;
	}
	else if (DesiredIndex >= SpellsIcons.Num())
	{
		DesiredIndex = 0;
	}

	return DesiredIndex;
}

void USpellsHUDWidget::NextSpell()
{
	CurrentSpellIcon = GetShiftedIndex(1);
	RefreshIcons();
}

void USpellsHUDWidget::PreviousSpell()
{
	CurrentSpellIcon = GetShiftedIndex(-1);
	RefreshIcons();
}