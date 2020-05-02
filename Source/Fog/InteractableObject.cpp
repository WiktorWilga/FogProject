// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "FogCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;

	InfoWidgetInst = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetInst->SetVisibility(false);
	InfoWidgetInst->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	InfoWidgetInst->SetWidgetClass(InfoWidgetClass);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractableObject::OnSphereOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractableObject::OnSphereOverlapEnd);
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObject::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AFogCharacter>(OtherActor);
	if (!Character) return;

	InfoWidgetInst->SetVisibility(true);

	OnHovered();
}

void AInteractableObject::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Character = Cast<AFogCharacter>(OtherActor);
	if (!Character) return;

	InfoWidgetInst->SetVisibility(false);

	OnUnhovered();
}

void AInteractableObject::OnHovered()
{
	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (!Character) return;

	Character->SetAvaliableInteraction(this);
}

void AInteractableObject::OnUnhovered()
{
	auto Character = Cast<AFogCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character) return;

	if (Character->GetAvaliableInteraction() == this)
	{
		Character->SetAvaliableInteraction(nullptr);
	}
}