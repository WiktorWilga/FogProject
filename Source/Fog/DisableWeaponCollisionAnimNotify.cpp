// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableWeaponCollisionAnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FightCharacter.h"

void UDisableWeaponCollisionAnimNotify::Notify(class USkeletalMeshComponent* MeshComponent, class UAnimSequenceBase* Animation)
{
	AFightCharacter* Character = Cast<AFightCharacter>(MeshComponent->GetOwner());
	if (!Character) return;

	Character->StopWeaponCheck();
}