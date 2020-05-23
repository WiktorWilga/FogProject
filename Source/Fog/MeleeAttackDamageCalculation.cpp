// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackDamageCalculation.h"
#include "FogAttributeSet.h"
#include "FightCharacter.h"

UMeleeAttackDamageCalculation::UMeleeAttackDamageCalculation()
{
	HealthProperty = FindFieldChecked<UProperty>(UFogAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UFogAttributeSet, Health));

	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
}

void UMeleeAttackDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	if (!ExecutionParams.GetTargetAbilitySystemComponent()) return;
	if (!ExecutionParams.GetSourceAbilitySystemComponent()) return;
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	
	AFightCharacter* TargetCharacter = Cast<AFightCharacter>(TargetASC->GetOwner());
	AFightCharacter* SourceCharacter = Cast<AFightCharacter>(SourceASC->GetOwner());

	if (!TargetCharacter || !SourceCharacter) return;

	float FinalDamage = 0.0f;
	FinalDamage += SourceCharacter->GetWeaponDamge();
	//@todo substract armor points from final damage

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}
