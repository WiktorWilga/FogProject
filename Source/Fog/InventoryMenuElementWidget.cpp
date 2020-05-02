// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuElementWidget.h"
#include "Components/Image.h"
#include "InventoryStructures.h"
#include "InventoryMenuWidget.h"

void UInventoryMenuElementWidget::SetData(FInventoryItem* Item, UInventoryMenuWidget* Parent)
{
	ItemData = Item;
	ParentWidget = Parent;

	ElementImage->SetBrushFromTexture(ItemData->Icon);
}

FReply UInventoryMenuElementWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton().ToString().Equals("LeftMouseButton"))
	{
		ParentWidget->OnClickedElement(ItemData);
	}

	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}
