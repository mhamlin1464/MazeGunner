// Copyright Epic Games, Inc. All Rights Reserved


#include "Gunner_Animation.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGunner_Animation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwningPawn = TryGetPawnOwner();

	if (!OwningPawn)
	{
		return;
	}

	//Cast to ACharcter to access movement componet
	ACharacter* Character = Cast<ACharacter>(OwningPawn);
	if (!Character)
	{
		return;
	}
	//Get The character's movement component
	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (!MovementComponent)
	{
		return;
	}
	//Update Speed
	FVector Velocity = Character->GetVelocity();
	speed = Velocity.Size();

	//Update Running State
	bIsRunning = (MovementComponent->MaxWalkSpeed > 600.0f);
}

