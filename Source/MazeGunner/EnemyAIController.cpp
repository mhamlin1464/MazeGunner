// Copyright Epic Games, Inc. All Rights Reserved

#include "EnemyAIController.h"



AEnemyAIController::AEnemyAIController()
{
	// Initialize the AIPerceptionComponent
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);
	// Initialize the Sight Config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.0f; // Set sight radius
	SightConfig->LoseSightRadius = 2500.0f; // Set lose sight radius
	SightConfig->PeripheralVisionAngleDegrees = 90.0f; // Set peripheral vision angle
	SightConfig->SetMaxAge(5.0f); // Set max age for sight perception
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//Do perception setup here if needed
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardAsset, Blackboard))
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//Set blackboard TargetActor key if player is seen
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor && Actor->IsA(AGunner_Player::StaticClass()))
		{
			// Assuming you have a blackboard key named "TargetActor"
			UE_LOG(LogTemp, Warning, TEXT("Enemy sees the player!"));
			if (Blackboard)
			{
				Blackboard->SetValueAsObject("TargetActor", Actor);
			}
			break; // Exit after finding the first player
		}
	}
}


