// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class FOG_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AEnemyController();

protected:

	/**AI perception for NPCs sight*/
	UPROPERTY(VisibleAnywhere, Category = "NPCAIController")
		class UPawnSensingComponent* PawnSensing;

	/**Blackboard component for BehaviorTree data*/
	class UBlackboardComponent* BlackboardComp;

	/**Behavior tree component for AI*/
	class UBehaviorTreeComponent* BehaviorTreeComp;

	/**Name of blackboard key for Target*/
	UPROPERTY(EditDefaultsOnly, Category = "NPCAIController")
		FName TargetKey;

	/**Name of blackboard key for damage raction state*/
	UPROPERTY(EditDefaultsOnly, Category = "NPCAIController")
		FName DamageRactionKey;

	/**Timer for wait to finish take damge raction*/
	FTimerHandle TakeDamageReactionTimer;

	UFUNCTION()
		void ResetTakeDamageReactionState();

public:

	/**Used to bind sensing functions, set behaior tree and blackboard*/
	virtual void OnPossess(APawn* Pawn) override;

	/**PawnSense call it when see player*/
	UFUNCTION()
		void OnSeePlayer(class APawn* ObservedPawn);

	void SetTakeDamageReactionForTime(float Time);

};
