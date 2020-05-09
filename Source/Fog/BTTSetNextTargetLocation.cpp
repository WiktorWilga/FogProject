// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTSetNextTargetLocation.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"

EBTNodeResult::Type UBTTSetNextTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		AEnemyCharacter* Character = Cast<AEnemyCharacter>(Controller->GetCharacter());
		if (Character)
		{
			UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
			if (Blackboard)
			{
				Blackboard->SetValueAsVector(TargetLocationKey, Character->GetNextTargetLocation());
				return EBTNodeResult::Type::Succeeded;
			}
		}
	}
	return EBTNodeResult::Type::Failed;
}