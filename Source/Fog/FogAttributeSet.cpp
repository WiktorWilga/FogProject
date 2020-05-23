// Fill out your copyright notice in the Description page of Project Settings.


#include "FogAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "FightCharacter.h"

UFogAttributeSet::UFogAttributeSet()
	: Health(200.0f), MaxHealth(200.0f)
{

}

void UFogAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<UProperty>(UFogAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UFogAttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetBaseValue()));
		HealthChanged.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		if (Health.GetCurrentValue() <= 0.0f)
		{
			AFightCharacter* Character = Cast<AFightCharacter>(GetOwningActor());
			if (Character)
			{
				Character->OnDead();
			}
		}
		
		/*AAssetsTestCharacter* Character = Cast< AAssetsTestCharacter>(GetOwningActor());
		if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
		{
			if (Character)
			{
				Character->AddGamepalyTag(Character->FullHealthTag);
			}
		}
		else
		{
			if (Character)
			{
				Character->RemoveGamepalyTag(Character->FullHealthTag);
			}
		}*/
	}
}
