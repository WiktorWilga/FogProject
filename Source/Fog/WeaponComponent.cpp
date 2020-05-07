// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponStructures.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	OnComponentBeginOverlap.AddDynamic(this, &UWeaponComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UWeaponComponent::OnOverlapEnd);

	//SetIsReplicated(true);
}

void UWeaponComponent::SetWeaponData(struct FWeaponInfo* NewWeaponData)
{
	if (!NewWeaponData) return;

	WeaponData = NewWeaponData;
	SetStaticMesh(WeaponData->Mesh.Get());
}

void UWeaponComponent::EnableCollisionCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("EnableC"));

	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UWeaponComponent::DisableCollisionCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("DisableC"));

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UWeaponComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
									  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision!"));
}

void UWeaponComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
									int32 OtherBodyIndex)
{

}