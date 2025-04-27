// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Gunner_Animation.h"
#include "Gunner_Player.generated.h"

UCLASS()
class MAZEGUNNER_API AGunner_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGunner_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector StandingCameraPosition = FVector(10.0f, 0.0f, 100.0f);
	FVector CrouchingCameraPosition = FVector(10.0f, 0.0f, 45.0f);
	//CameraTransitionAlpha = 0.0f; currently represents standing
	float CameraTransitionAlpha = 0.0f;
	float CameraTransitionSpeed = 1.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Functions for moving player forward and right
	UFUNCTION()
	void MoveForward(float input_value);

	UFUNCTION()
	void MoveRight(float input_value);

	//Functions for Sprinting
	UFUNCTION()
	void StartSprinting();

	UFUNCTION()
	void StopSprinting();

	//Functions for Jumping
	UFUNCTION()
	void StartJumping();
	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void ImCrouch();

	UFUNCTION()
	void NotCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Gunner_Camera;

	UPROPERTY()
	class UGunner_Animation* MyAnimInstance;
};
