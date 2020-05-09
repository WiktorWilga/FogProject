// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTSetSpeed.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyCharacter.h"

EBTNodeResult::Type UBTTSetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		AEnemyCharacter* Character = Cast<AEnemyCharacter>(Controller->GetCharacter());
		if (Character)
		{
			Character->GetCharacterMovement()->MaxWalkSpeed = Speed;
			return EBTNodeResult::Type::Succeeded;
		}
	}
	return EBTNodeResult::Type::Failed;
}
