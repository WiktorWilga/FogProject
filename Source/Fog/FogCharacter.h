// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	void AddPickUpObjectToInventory(FName PickUpName, uint32 Amount = 1);
	void RemovePickUpObjectFromInventory(FName PickUpName, uint32 Amount = 1);

	/** Getter for character inventory*/
	FORCEINLINE TArray<FInventoryItemWithCounter> GetInventory() { return Inventory; }

	/**Getter/setter for character's weapon*/
	FORCEINLINE struct FInventoryItem* GetWeapon() { return Weapon; }
	FORCEINLINE void SetWeapon(struct FInventoryItem* NewWeapon) { Weapon = NewWeapon; }

	/**Getter/setter for character's armor*/
	FORCEINLINE struct FInventoryItem* GetArmor() { return Armor; }
	FORCEINLINE void SetArmor(struct FInventoryItem* NewArmor) { Armor = NewArmor; }

	/**Getter/setter fo current interactable object in avaliable range*/
	FORCEINLINE void SetAvaliableInteraction(class AInteractableObject* Object) { Server_AvaliableInteraction = Object; }
	FORCEINLINE class AInteractableObject* GetAvaliableInteraction() { return Server_AvaliableInteraction; }

	/**Perform interaction with current selected avaliable object*/
	UFUNCTION(Server, Reliable)
	void Server_MakeCurrentInteraction();

	/**Start attack animation if isnt performing now*/
	UFUNCTION(Server, Reliable)
	void Server_PerformAttack();

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
	struct FInventoryItem* Weapon;
	struct FInventoryItem* Armor;

	/**Current selected object to interaction*/
	class AInteractableObject* Server_AvaliableInteraction = nullptr;

	/**Return array index if given name is in inventory or -1 if isnt*/
	int32 GetInventoryItemIndex(FName Name);

	/**Combat system's animations*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* FirstAttackAnim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* SecondAttackAnim;

	/**Attack in series counter*/
	uint8 CurrentAttack = 0;

	/**Return true if character is playing attack anim at this moment*/
	bool IsPerformingAttack();

	/**Play given montage on every machines*/
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_PlayMontage(class UAnimMontage* AnimMontage);

};

