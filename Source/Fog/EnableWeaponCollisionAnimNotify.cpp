// Fill out your copyright notice in the Description page of Project Settings.


#include "EnableWeaponCollisionAnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FogCharacter.h"

void UEnableWeaponCollisionAnimNotify::Notify(USkeletalMeshComponent* MeshComponent, UAnimSequenceBase* Animation)
{
	AFogCharacter* Character = Cast<AFogCharacter>(MeshComponent->GetOwner());
	if (!Character) return;

	Character->StartWeaponCheck();
}
