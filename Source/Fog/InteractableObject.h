// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS(Abstract)
class FOG_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

private:

	UFUNCTION()
		void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USphereComponent* CollisionSphere;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UWidgetComponent* InfoWidgetInst;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() {};

	/**Called when character begin/end overlap collision sphere*/
	virtual void OnHovered();
	virtual void OnUnhovered();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> InfoWidgetClass;

};
