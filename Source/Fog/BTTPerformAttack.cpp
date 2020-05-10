// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTPerformAttack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyCharacter.h"

EBTNodeResult::Type UBTTPerformAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		AEnemyCharacter* Character = Cast<AEnemyCharacter>(Controller->GetCharacter());
		if (Character)
		{
			Character->Server_PerformAttack();
			return EBTNodeResult::Type::Succeeded;
		}
	}
	return EBTNodeResult::Type::Failed;
}
