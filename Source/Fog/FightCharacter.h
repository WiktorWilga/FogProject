// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FightCharacter.generated.h"

UCLASS()
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

protected:

	float Health;
	float MaxHealth = 100;
};
