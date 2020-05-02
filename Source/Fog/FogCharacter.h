// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FogCharacter.generated.h"


UCLASS(Blueprintable)
class AFogCharacter : public ACharacter
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
	UFUNCTION(BlueprintCallable)
	void AddPickUpObjectToInventory(FName PickUpName, int32 Amount = 1);
	UFUNCTION(BlueprintCallable)
	void RemovePickUpObjectFromInventory(FName PickUpName, int32 Amount = 1);

	/** Getter for character inventory*/
	FORCEINLINE TMap<FName, int32> GetInventory() { return Inventory; }

	/**Getter/setter for character's weapon*/
	FORCEINLINE struct FInventoryItem* GetWeapon() { return Weapon; }
	FORCEINLINE void SetWeapon(struct FInventoryItem* NewWeapon) { Weapon = NewWeapon; }

	/**Getter/setter for character's armor*/
	FORCEINLINE struct FInventoryItem* GetArmor() { return Armor; }
	FORCEINLINE void SetArmor(struct FInventoryItem* NewArmor) { Armor = NewArmor; }

	/**Getter/setter fo current interactable object in avaliable range*/
	FORCEINLINE void SetAvaliableInteraction(class AInteractableObject* Object) { AvaliableInteraction = Object; }
	FORCEINLINE class AInteractableObject* GetAvaliableInteraction() { return AvaliableInteraction; }

	/**Perform interaction with current selected avaliable object*/
	void MakeCurrentInteraction();

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
	TMap<FName, int32> Inventory;
	struct FInventoryItem* Weapon;
	struct FInventoryItem* Armor;

	/**Current selected object to interaction*/
	class AInteractableObject* AvaliableInteraction = nullptr;

};

