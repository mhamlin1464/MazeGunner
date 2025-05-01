// Copyright Epic Games, Inc. All Rights Reserved


#include "APickupItem.h"

// Sets default values
AAPickupItem::AAPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the static mesh component
	PickupItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupItem"));
	SetRootComponent(PickupItem);
	PickupItem->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupItem->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	//Load a default static mesh for the PickupItem
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/LP_LiteWeapons_JC/Models/SM_Weapons_04_MERGED.SM_Weapons_04_MERGED"));
	if (MeshAsset.Succeeded())
	{
		PickupItem->SetStaticMesh(MeshAsset.Object);
	}
	//Creates and Sets up the Collision Box
	ItemCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionBox"));
	ItemCollisionBox->SetupAttachment(PickupItem);
	ItemCollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	ItemCollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ItemCollisionBox->SetGenerateOverlapEvents(true);

	OverlappingCharacter = nullptr;
	bIsPickedUp = false;
}

// Called when the game starts or when spawned
void AAPickupItem::BeginPlay()
{
	Super::BeginPlay();

	ItemCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAPickupItem::HandleOverlap);

	
}

// Called every frame
void AAPickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAPickupItem::OnPickup()
{
	bIsPickedUp = true; // Mark the weapon as picked up
	//Destroy();
}

void AAPickupItem::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()) && !bIsPickedUp)
	{
		OverlappingCharacter = Cast<ACharacter>(OtherActor); // Stores the reference to the character
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Pickup Item"));
	}
}

void AAPickupItem::AttachToCharacter()
{
	bIsPickedUp = true; // Marks the weapon as picked up
	PickupItem->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Attached the item
	if (OverlappingCharacter)
	{
		USkeletalMeshComponent* CharacterMesh = OverlappingCharacter->GetMesh();
		if (CharacterMesh)
		{
			PickupItem->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ik_hand_r_gun_socket"));
		}
	}

}
