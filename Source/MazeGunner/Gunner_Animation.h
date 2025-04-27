// Copyright Epic Games, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Gunner_Animation.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGUNNER_API UGunner_Animation : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bIsRunning;
	
};
