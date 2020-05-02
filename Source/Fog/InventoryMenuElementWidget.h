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

	void SetData(struct FInventoryItem* Item, class UInventoryMenuWidget* Parent);

protected:

	FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,const FPointerEvent& InMouseEvent) override;
	
private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UImage* ElementImage;
	
	struct FInventoryItem* ItemData;

	UPROPERTY()
		class UInventoryMenuWidget* ParentWidget;

};
