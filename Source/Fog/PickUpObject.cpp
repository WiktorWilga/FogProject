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

void APickUpObject::Interact()
{
	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character) return;

	for (TPair<FName, int32> Element : Inventory)
	{
		Character->AddPickUpObjectToInventory(Element.Key, Element.Value);
	}

	Destroy();
}

void APickUpObject::OnHovered()
{
	Super::OnHovered();
}

void APickUpObject::OnUnhovered()
{
	Super::OnUnhovered();
}
