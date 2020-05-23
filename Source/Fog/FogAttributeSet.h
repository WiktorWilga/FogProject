// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FogAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeChangedDelegate, float, CurrentValue, float, MaxValue);

UCLASS()
class FOG_API UFogAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UFogAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData MaxHealth;

	FAttributeChangedDelegate HealthChanged;
};
