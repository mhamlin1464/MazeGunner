// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeGunner_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGUNNER_API AMazeGunner_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
};
