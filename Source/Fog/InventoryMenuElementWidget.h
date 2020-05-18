// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenuElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class FOG_API UInventoryMenuElementWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetData(FName Name, struct FInventoryItem* Item, class UInventoryMenuWidget* Parent);
	struct FInventoryItem* GetData();
	FName GetItemName() { return ItemName; }

protected:

	FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,const FPointerEvent& InMouseEvent) override;
	
private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UImage* ElementImage;
	
	FName ItemName;
	struct FInventoryItem* ItemData;

	UPROPERTY()
		class UInventoryMenuWidget* ParentWidget;

};
