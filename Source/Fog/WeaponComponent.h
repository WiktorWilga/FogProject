// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"


UCLASS()
class FOG_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent(const FObjectInitializer& ObjectInitializer);

public:	

	void SetWeaponData(struct FWeaponInfo* NewWeaponData);

	FORCEINLINE struct FWeaponInfo* GetWeaponData() { return WeaponData; }

	void EnableCollisionCheck();
	void DisableCollisionCheck();

private:

	struct FWeaponInfo* WeaponData;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
};
