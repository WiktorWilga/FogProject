// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "PickUpObject.generated.h"

UCLASS()
class FOG_API APickUpObject : public AInteractableObject
{
	GENERATED_BODY()
	
public:	

	APickUpObject();
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class AFogCharacter* Invoker) override;
	virtual void OnHovered(class AFogCharacter* Invoker) override;
	virtual void OnUnhovered(class AFogCharacter* Invoker) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	TMap<FName, int32> Inventory;
};
