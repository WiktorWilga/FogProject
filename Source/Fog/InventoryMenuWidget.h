// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStructures.h"
#include "InventoryMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FOG_API UInventoryMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	bool Initialize() override;

	void OnClickedElement(FName ItemName, struct FInventoryItem* ElementItem);

protected:

	void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* WeaponButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* ArmorButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* FoodButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* OtherButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UWidgetSwitcher* TypeWidgetSwitcher;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UWrapBox* WeaponWrapBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UWrapBox* ArmorWrapBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UWrapBox* FoodWrapBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UWrapBox* OtherWrapBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UOverlay* WeaponOverlay;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UOverlay* ArmorOverlay;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UHorizontalBox* SpellsSlotsHorizontalBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UOverlay* SpellOverlay1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UOverlay* SpellOverlay2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UOverlay* SpellOverlay3;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UOverlay* SpellOverlay4;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UInventoryMenuElementWidget> ElementClass;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* InventoryDataTable;

	void Setup();

	UFUNCTION()
		void OnWeapon();
	UFUNCTION()
		void OnArmor();
	UFUNCTION()
		void OnFood();
	UFUNCTION()
		void OnOther();

	void ClearWrapBoxes();
	void AddElementToWrapBox(class UInventoryMenuElementWidget* Element, EInventoryType Type);

	void SetSlot(FName ItemName, struct FInventoryItem* NewSlotItem);

	void SetCharacterWeapon(FName ItemName);

	class UOverlay* GetFirstFreeSpellSlot();

	class UInventoryMenuElementWidget* GetInventoryElemntInside(class UOverlay* Overlay);
};
