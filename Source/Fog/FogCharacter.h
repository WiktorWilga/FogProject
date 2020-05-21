// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FightCharacter.h"
#include "WeaponStructures.h"
#include "FogCharacter.generated.h"

USTRUCT()
struct FInventoryItemWithCounter
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FName Name;

	UPROPERTY()
		uint32 Num;

	FInventoryItemWithCounter() : Name(""), Num(0) {}
	FInventoryItemWithCounter(FName NewName, uint32 NewNum) : Name(NewName), Num(NewNum) {}
};


UCLASS(Blueprintable)
class AFogCharacter : public AFightCharacter
{
	GENERATED_BODY()

public:
	AFogCharacter();

	void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Add/remove from inventory*/
	void AddPickUpObjectToInventory(FName PickUpName, uint32 Amount = 1);
	void RemovePickUpObjectFromInventory(FName PickUpName, uint32 Amount = 1);

	/** Return true if character has object of given name*/
	bool HasItem(FName PickUpName);

	/** Getter for character inventory*/
	FORCEINLINE TArray<FInventoryItemWithCounter> GetInventory() { return Inventory; }

	/**Getter/setter for character's weapon*/
	FWeaponInfo* GetWeapon();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetWeapon(FName WeaponName);

	/**Getter/setter for character's armor*/
	FORCEINLINE struct FInventoryItem* GetArmor() { return Armor; }
	FORCEINLINE void SetArmor(struct FInventoryItem* NewArmor) { Armor = NewArmor; }

	/**Getter/setter fo current interactable object in avaliable range*/
	FORCEINLINE void SetAvaliableInteraction(class AInteractableObject* Object) { Server_AvaliableInteraction = Object; }
	FORCEINLINE class AInteractableObject* GetAvaliableInteraction() { return Server_AvaliableInteraction; }

	/**Perform interaction with current selected avaliable object*/
	UFUNCTION(Server, Reliable)
	void Server_MakeCurrentInteraction();

	/**Return true if givan character is this characer enemy*/
	virtual bool IsEnemy(AFightCharacter* Character) override;

	/**Start making dodge*/
	UFUNCTION(Server, Reliable)
	void Server_StartDodge();

	/**Set spells, when player close inventory*/
	void SetSelectedSpells(TArray<FName> SpellsNames);

	/**Set previous spell as current*/
	void PreviousSpell();

	/**Set next spell as current*/
	void NextSpell();

	/**Try run on selected spell; send request to server*/
	void Client_UseSelectedSpell();

	/** Use spell*/
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseSpell(FName Spell);

	/**Add new functionality to refresh client healt widget*/
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser) override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	/** Cursor material instance*/
	UPROPERTY()
		class UMaterialInstanceDynamic* CursorMaterial;

	/** Set in editor material*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UMaterialInstance* CursorMaterialInstance;

	/**Set cursor location*/
	void CursorTick();

	/**Rotate character to cursorr with avaliable speed*/
	void RotateCharacterToCursor(float DeltaSeconds);

	/** Character inventory*/
	UPROPERTY(Replicated)
	TArray<FInventoryItemWithCounter> Inventory;
	struct FInventoryItem* Armor;

	/**Current selected object to interaction*/
	class AInteractableObject* Server_AvaliableInteraction = nullptr;

	/**Return array index if given name is in inventory or -1 if isnt*/
	int32 GetInventoryItemIndex(FName Name);

	/**Reference to weapons data table*/
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* WeaponDataTable;

	/**How far/fast can character dodge*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float DodgeStrength = 30000000.0f;

	/**Spells which character can currently use*/
	UPROPERTY()
	TArray<FName> SelectedSpells;

	/**Currently selected spell, this one which player can actually use*/
	uint8 CurrentSpell = 0;

	/**Reference to spells data table*/
	UPROPERTY(EditDefaultsOnly)
		class UDataTable* SpellsDataTable;

	/**Return specified index of spells array*/
	uint8 GetShiftedIndex(int8 Offset);

	/**Called to refresh client's hud health bar*/
	UFUNCTION(Client, Reliable)
		void Client_RefreshHealthWidget(float CurrentPercent);

};

