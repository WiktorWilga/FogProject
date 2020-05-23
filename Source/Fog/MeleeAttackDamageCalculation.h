// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MeleeAttackDamageCalculation.generated.h"

/**
 * 
 */
UCLASS()
class FOG_API UMeleeAttackDamageCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:

	UMeleeAttackDamageCalculation();

	UProperty* HealthProperty;

	FGameplayEffectAttributeCaptureDefinition HealthDef;

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
};
