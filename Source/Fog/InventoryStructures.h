// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryStructures.generated.h"

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	IT_Weapon, 
	IT_Armor, 
	IT_Spell, 
	IT_Other
};

UENUM(BlueprintType)
enum class EInventoryDetailsType : uint8
{
	IDT_AddHP,
	IDT_AddXP
};

USTRUCT(BlueprintType)
struct FInventoryDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInventoryDetailsType DetailsType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value;

};

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

	//Name is automaticly added as row key

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInventoryType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInventoryDetails> Details;
};