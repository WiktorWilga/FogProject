// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpellStructures.generated.h"


USTRUCT(BlueprintType)
struct FSpellInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UGameplayAbility> Ability;

};