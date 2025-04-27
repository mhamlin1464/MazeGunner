// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGunner_GameMode.h"


void AMazeGunner_GameMode::StartPlay()
{
	Super::StartPlay();
	// Add your custom logic here
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("MazeGunner Game Mode Started"));
	
}
