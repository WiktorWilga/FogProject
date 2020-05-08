// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FogCharacter.h"
#include "EnemyCharacter.h"


AEnemyController::AEnemyController()
{
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
}

void AEnemyController::OnPossess(APawn* MyPawn)
{
	Super::OnPossess(MyPawn);

	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyController::OnSeePlayer);

	AEnemyCharacter* NPCCharacter = Cast<AEnemyCharacter>(MyPawn);
	if (NPCCharacter && NPCCharacter->BehaviorTree && NPCCharacter->BehaviorTree->BlackboardAsset)
	{
		//Initialize the blackboard values
		BlackboardComp->InitializeBlackboard(*NPCCharacter->BehaviorTree->BlackboardAsset);
		//Start the tree
		BehaviorTreeComp->StartTree(*NPCCharacter->BehaviorTree);
	}
}

void AEnemyController::OnSeePlayer(APawn* ObservedPawn)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "see");

	AEnemyCharacter* MyCharacter = Cast<AEnemyCharacter>(GetPawn());
	AFogCharacter* ObservedCharacter = Cast<AFogCharacter>(ObservedPawn);

	if (MyCharacter && ObservedCharacter)
	{
		BlackboardComp->SetValueAsObject(TargetKey, ObservedCharacter);
	}
}