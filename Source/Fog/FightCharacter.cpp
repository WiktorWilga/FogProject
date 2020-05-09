// Fill out your copyright notice in the Description page of Project Settings.


#include "FightCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Weapon.h"

// Sets default values
AFightCharacter::AFightCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = MaxHealth;
}

// Called when the game starts or when spawned
void AFightCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AFightCharacter::TakeDamage);
}

// Called every frame
void AFightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFightCharacter::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0.0f)
	{
		Server_Death();
		NetMulticast_Death();
	}

}

void AFightCharacter::NetMulticast_Death_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AFightCharacter::Server_Death_Implementation()
{
	Controller->UnPossess();
}

void AFightCharacter::Server_PerformAttack_Implementation()
{
	if (IsPerformingAttack()) return;

	if (!Weapon) return;

	AWeapon* MyWeapon = Cast<AWeapon>(Weapon->GetChildActor());
	if (!MyWeapon) return;

	if (!MyWeapon->GetWeaponData()) return;

	++CurrentAttack;
	CurrentAttack %= AttackAnims.Num();

	NetMulticast_PlayMontage(AttackAnims[CurrentAttack]);
}

bool AFightCharacter::IsPerformingAttack()
{
	return (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackAnims[CurrentAttack]));
}

void AFightCharacter::NetMulticast_PlayMontage_Implementation(class UAnimMontage* AnimMontage)
{
	PlayAnimMontage(AnimMontage);
}

void AFightCharacter::StartWeaponCheck()
{
	if (!Weapon) return;

	AWeapon* MyWeapon = Cast<AWeapon>(Weapon->GetChildActor());
	if (!MyWeapon) return;

	MyWeapon->EnableCollisionCheck();
}

void AFightCharacter::StopWeaponCheck()
{
	if (!Weapon) return;

	AWeapon* MyWeapon = Cast<AWeapon>(Weapon->GetChildActor());
	if (!MyWeapon) return;

	MyWeapon->DisableCollisionCheck();
}