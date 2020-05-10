// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Weapon.h"
#include "WeaponStructures.h"
#include "FogCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	OffsetLocation = GetActorLocation();

	SetupEnemyWeapon();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AEnemyCharacter::GetNextTargetLocation()
{
	++CurrentTargetLocation;
	CurrentTargetLocation %= TargetLocations.Num();

	return (TargetLocations[CurrentTargetLocation] + OffsetLocation);
}

void AEnemyCharacter::SetupEnemyWeapon()
{
	AWeapon* MyWeapon = Cast<AWeapon>(WeaponComponent->GetChildActor());
	if (MyWeapon && !WeaponRef.IsNull())
	{
		FString Context;
		MyWeapon->SetWeaponData(WeaponRef.GetRow<FWeaponInfo>(Context));
	}
}

bool AEnemyCharacter::IsEnemy(AFightCharacter* Character)
{
	return Character->IsA<AFogCharacter>();
}
