// Copyright Epic Games, Inc. All Rights Reserved


#include "AEnemyCharcter.h"

// Sets default values
AAEnemyCharcter::AAEnemyCharcter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize Health
	Health = 100.0f;

	//Setting AI Controller Class
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AAEnemyCharcter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAEnemyCharcter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAEnemyCharcter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Function to take damage
float AAEnemyCharcter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Enemy took damage! Health: %f"), Health);
	if (Health <= 0.0f)
	{
		//Destroy Enemy Character
		Destroy();
	}
	
	return DamageAmount;
	
}

