// Copyright Epic Games, Inc. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "APickupItem.generated.h"

UCLASS()
class MAZEGUNNER_API AAPickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup Item")
	UStaticMeshComponent* PickupItem;

	UPROPERTY(Editanywhere,BlueprintReadWrite,Category = "Pickup Item")
	UBoxComponent* ItemCollisionBox;

	UFUNCTION()	
	void OnPickup();

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	

};
