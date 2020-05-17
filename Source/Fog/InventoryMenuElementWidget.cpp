// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuElementWidget.h"
#include "Components/Image.h"
#include "InventoryStructures.h"
#include "InventoryMenuWidget.h"

void UInventoryMenuElementWidget::SetData(FName Name, FInventoryItem* Item, UInventoryMenuWidget* Parent)
{
	ItemName = Name;
	ItemData = Item;
	ParentWidget = Parent;

	ElementImage->SetBrushFromTexture(ItemData->Icon);
}

FReply UInventoryMenuElementWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton().ToString().Equals("LeftMouseButton"))
	{
		ParentWidget->OnClickedElement(ItemName, ItemData);
	}

	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

FInventoryItem* UInventoryMenuElementWidget::GetData()
{
	return ItemData;
}