// Fill out your copyright notice in the Description page of Project Settings.


#include "DisableWeaponCollisionAnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FogCharacter.h"

void UDisableWeaponCollisionAnimNotify::Notify(class USkeletalMeshComponent* MeshComponent, class UAnimSequenceBase* Animation)
{
	AFogCharacter* Character = Cast<AFogCharacter>(MeshComponent->GetOwner());
	if (!Character) return;

	Character->StopWeaponCheck();
}