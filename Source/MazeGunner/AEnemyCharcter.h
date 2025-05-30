// Copyright Epic Games, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAIController.h"
#include "AEnemyCharcter.generated.h"

UCLASS()
class MAZEGUNNER_API AAEnemyCharcter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAEnemyCharcter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Health Variable
	float Health = 100.0f;

	//Function to take damage
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
