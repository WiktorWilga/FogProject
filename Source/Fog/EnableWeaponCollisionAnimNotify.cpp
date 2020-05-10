// Fill out your copyright notice in the Description page of Project Settings.


#include "EnableWeaponCollisionAnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FightCharacter.h"

void UEnableWeaponCollisionAnimNotify::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	AFightCharacter* Character = Cast<AFightCharacter>(MeshComponent->GetOwner());
	if (!Character) return;

	Character->StartWeaponCheck();
}
