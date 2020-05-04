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
			NewElement->SetData(ItemData, this);

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
	case EInventoryType::IT_Food:
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

void UInventoryMenuWidget::OnClickedElement(struct FInventoryItem* ElementItem)
{
	if (!ElementItem) return;

	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character) return;

	switch (ElementItem->Type)
	{
	case EInventoryType::IT_Weapon:
		Character->SetWeapon(ElementItem); 
		SetSlot(ElementItem);
		break;
	case EInventoryType::IT_Armor:
		Character->SetArmor(ElementItem);
		SetSlot(ElementItem);
		break;
	case EInventoryType::IT_Food:
		break;
	case EInventoryType::IT_Other:
		break;
	}
}

void UInventoryMenuWidget::SetSlot(struct FInventoryItem* NewSlotItem)
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
	default:
		DesiredOverlay = nullptr;
	}

	if (!DesiredOverlay) return;

	for (UWidget* Child : DesiredOverlay->GetAllChildren())
	{
		auto CurrentWeapon = Cast<UInventoryMenuElementWidget>(Child);
		if (CurrentWeapon)
		{
			CurrentWeapon->SetData(NewSlotItem, this);
			return;
		}
	}

	UInventoryMenuElementWidget* NewElement = CreateWidget<UInventoryMenuElementWidget>(this, ElementClass);
	NewElement->SetData(NewSlotItem, this);
	DesiredOverlay->AddChildToOverlay(NewElement);
}