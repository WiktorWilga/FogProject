// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuWidget.h"
#include "Engine/DataTable.h"
#include "FogCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "InventoryMenuElementWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"

bool UInventoryMenuWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!WeaponButton) return false;
	WeaponButton->OnClicked.AddDynamic(this, &UInventoryMenuWidget::OnWeapon);

	if (!ArmorButton) return false;
	ArmorButton->OnClicked.AddDynamic(this, &UInventoryMenuWidget::OnArmor);

	if (!FoodButton) return false;
	FoodButton->OnClicked.AddDynamic(this, &UInventoryMenuWidget::OnFood);

	if (!OtherButton) return false;
	OtherButton->OnClicked.AddDynamic(this, &UInventoryMenuWidget::OnOther);

	return true;
}

void UInventoryMenuWidget::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	Super::AddToScreen(LocalPlayer, ZOrder);

	Setup();
}

void UInventoryMenuWidget::Setup()
{
	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character)
	{
		ClearWrapBoxes();

		for (FInventoryItemWithCounter Item : Character->GetInventory())
		{
			const FString Context;
			FInventoryItem* ItemData = InventoryDataTable->FindRow<FInventoryItem>(Item.Name, Context);

			UInventoryMenuElementWidget* NewElement = CreateWidget<UInventoryMenuElementWidget>(this, ElementClass);
			NewElement->SetData(Item.Name, ItemData, this);

			AddElementToWrapBox(NewElement, ItemData->Type);
		}
	}
}

void UInventoryMenuWidget::ClearWrapBoxes()
{
	WeaponWrapBox->ClearChildren();
	ArmorWrapBox->ClearChildren();
	FoodWrapBox->ClearChildren();
	OtherWrapBox->ClearChildren();
}

void UInventoryMenuWidget::AddElementToWrapBox(UInventoryMenuElementWidget* Element, EInventoryType Type)
{
	switch (Type)
	{
	case EInventoryType::IT_Weapon:
		WeaponWrapBox->AddChildToWrapBox(Element);
		break;
	case EInventoryType::IT_Armor:
		ArmorWrapBox->AddChildToWrapBox(Element);
		break;
	case EInventoryType::IT_Spell:
		FoodWrapBox->AddChildToWrapBox(Element);
		break;
	case EInventoryType::IT_Other:
		OtherWrapBox->AddChildToWrapBox(Element);
		break;
	}
}

void UInventoryMenuWidget::OnWeapon()
{
	TypeWidgetSwitcher->SetActiveWidget(WeaponWrapBox);
}

void UInventoryMenuWidget::OnArmor()
{
	TypeWidgetSwitcher->SetActiveWidget(ArmorWrapBox);
}

void UInventoryMenuWidget::OnFood()
{
	TypeWidgetSwitcher->SetActiveWidget(FoodWrapBox);
}

void UInventoryMenuWidget::OnOther()
{
	TypeWidgetSwitcher->SetActiveWidget(OtherWrapBox);
}

void UInventoryMenuWidget::OnClickedElement(FName ItemName, FInventoryItem* ElementItem)
{
	if (!ElementItem) return;

	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character) return;

	switch (ElementItem->Type)
	{
	case EInventoryType::IT_Weapon:
		SetCharacterWeapon(ItemName);
		SetSlot(ItemName, ElementItem);
		break;
	case EInventoryType::IT_Armor:
		Character->SetArmor(ElementItem);
		SetSlot(ItemName, ElementItem);
		break;
	case EInventoryType::IT_Spell:
		SetSlot(ItemName, ElementItem);
		break;
	case EInventoryType::IT_Other:
		break;
	}
}

void UInventoryMenuWidget::SetSlot(FName ItemName, FInventoryItem* NewSlotItem)
{
	if (!NewSlotItem) return;

	UOverlay* DesiredOverlay;
	switch (NewSlotItem->Type)
	{
	case EInventoryType::IT_Armor:
		DesiredOverlay = WeaponOverlay;
		break;
	case EInventoryType::IT_Weapon:
		DesiredOverlay = ArmorOverlay;
		break;
	case EInventoryType::IT_Spell:
		DesiredOverlay = GetFirstFreeSpellSlot();
		break;
	default:
		DesiredOverlay = nullptr;
	}

	if (!DesiredOverlay) return;

	UInventoryMenuElementWidget* CurrentWeapon = GetInventoryElemntInside(DesiredOverlay);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetData(ItemName, NewSlotItem, this);
		return;
	}

	UInventoryMenuElementWidget* NewElement = CreateWidget<UInventoryMenuElementWidget>(this, ElementClass);
	NewElement->SetData(ItemName, NewSlotItem, this);
	DesiredOverlay->AddChildToOverlay(NewElement);
}

void UInventoryMenuWidget::SetCharacterWeapon(FName ItemName)
{
	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character) return;

	Character->Server_SetWeapon(ItemName);
}

UOverlay* UInventoryMenuWidget::GetFirstFreeSpellSlot()
{
	if (!GetInventoryElemntInside(SpellOverlay1)) return SpellOverlay1;
	if (!GetInventoryElemntInside(SpellOverlay2)) return SpellOverlay2;
	if (!GetInventoryElemntInside(SpellOverlay3)) return SpellOverlay3;
	if (!GetInventoryElemntInside(SpellOverlay4)) return SpellOverlay4;
	return nullptr;
}

UInventoryMenuElementWidget* UInventoryMenuWidget::GetInventoryElemntInside(UOverlay* Overlay)
{
	if (!Overlay) return nullptr;

	for (UWidget* Child : Overlay->GetAllChildren())
	{
		auto CurrentWeapon = Cast<UInventoryMenuElementWidget>(Child);
		if (CurrentWeapon)
		{
			return CurrentWeapon;
		}
	}

	return nullptr;
}