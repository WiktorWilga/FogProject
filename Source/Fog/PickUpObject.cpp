// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpObject.h"
#include "Components/StaticMeshComponent.h"
#include "FogCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

// Sets default values
APickUpObject::APickUpObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(CollisionSphere);
}

// Called when the game starts or when spawned
void APickUpObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpObject::Interact(class AFogCharacter* Invoker)
{
	if (!Invoker) return;

	for (TPair<FName, int32> Element : Inventory)
	{
		Invoker->AddPickUpObjectToInventory(Element.Key, Element.Value);
	}

	Destroy();
}

void APickUpObject::OnHovered(class AFogCharacter* Invoker)
{
	Super::OnHovered(Invoker);
}

void APickUpObject::OnUnhovered(class AFogCharacter* Invoker)
{
	Super::OnUnhovered(Invoker);
}
