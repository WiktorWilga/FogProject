// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FightCharacter.generated.h"

UCLASS(Abstract)
class FOG_API AFightCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
			class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(NetMulticast, Reliable)
	virtual void NetMulticast_Death();

	UFUNCTION(Server, Reliable)
	virtual void Server_Death();

	/**Start attack animation if isnt performing now*/
	UFUNCTION(Server, Reliable)
		virtual void Server_PerformAttack();

	/**Weapon checking collison*/
	void StartWeaponCheck();
	void StopWeaponCheck();

	/**Return true if givan character is this characer enemy*/
	virtual bool IsEnemy(AFightCharacter* Character) PURE_VIRTUAL(AFightCharacter::IsEnemy, return false;);
	
	/**Adding new ability to ability component*/
	UFUNCTION(BlueprintCallable)
		void AddAbility(TSubclassOf<class UGameplayAbility> AbilityClass);

	/**Set currently avaliable spells for character*/
	void SetSelectedSpells(TArray<TSubclassOf<class UGameplayAbility>> InSelectedSpells);

protected:

	float Health;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	/** Weapon component for combat system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* WeaponComponent;

	/**Combat system's animations*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<class UAnimMontage*> AttackAnims;

	/**Attack in series counter*/
	uint8 CurrentAttack = 0;

	/**Return true if character is playing attack anim at this moment*/
	bool IsPerformingAttack();

	/**Play given montage on every machines*/
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_PlayMontage(class UAnimMontage* AnimMontage);

	/**Component for ability system*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UAbilitySystemComponent* AbilityComponent;

	/**Spells which character can currently use*/
	UPROPERTY()
		TArray<TSubclassOf<class UGameplayAbility>> SelectedSpells;
};
