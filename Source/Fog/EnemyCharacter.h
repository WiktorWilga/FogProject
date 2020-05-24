// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightCharacter.h"
#include "Engine/DataTable.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FOG_API AEnemyCharacter : public AFightCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;

	FVector GetNextTargetLocation();

	/**Return true if givan character is this characer enemy*/
	virtual bool IsEnemy(AFightCharacter* Character) override;

	//deprecated - now Gameplay Ability System is in use
	/*virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser) override;*/

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HealthWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* TakeDamageReactionAnim;

	/**Stop enemy for time when TakeDamageReaction is playing*/
	virtual void MakeTakeDamageReaction() override;

private:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, meta = (AllowPrivateAccess = true))
		class UWidgetComponent* HealthWidget;


	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
		TArray<FVector> TargetLocations;

	/** Character start location; used to calculate true location from TargetLocations, which are relative location*/
	FVector OffsetLocation;

	uint8 CurrentTargetLocation = 0;

	/** Set weapon component from selected weapon row from data table (WeaponRef)*/
	void SetupEnemyWeapon();

	/** Reference to weapon data table row*/
	UPROPERTY(EditAnywhere)
		FDataTableRowHandle WeaponRef;

	/**Set health bar widget value*/
	UFUNCTION(NetMulticast, Unreliable)
		void NetMulticast_RefreshHealthBar(float Current, float Max);
};
