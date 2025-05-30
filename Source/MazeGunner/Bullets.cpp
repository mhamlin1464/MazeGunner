// Copyright Epic Games, Inc. All Rights Reserved

#include "AEnemyCharcter.h"
#include "Bullets.h"

// Sets default values
ABullets::ABullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the root component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);

	// Set up projectile movement component
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	BulletMovement->InitialSpeed = 6000.0f;
	BulletMovement->MaxSpeed = 6000.0f;
	BulletMovement->ProjectileGravityScale = 0.0f;//No gravity

	//Set up for static mesh component
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	//RootComponent = BulletMesh;
	//Setup Collision to detect overlaps
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	BulletMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	BulletMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECollisionResponse::ECR_Block);
	BulletMesh->SetSimulatePhysics(false);

	//Binding the OnHit function to the Hit event
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABullets::OnHit);

	
	

	//Delete the bullet after 3 seconds 
	InitialLifeSpan = 3.0f;

	
	
}

// Called when the game starts or when spawned
void ABullets::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABullets::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the bullet hit an enemy character
	if (OtherActor && OtherActor != this)
	{
		AAEnemyCharcter* EnemyCharacter = Cast<AAEnemyCharcter>(OtherActor);
		if (EnemyCharacter)
		{
			// Deal damage to the enemy character
			float DamageAmount = 20.0f; // Example damage amount
			UGameplayStatics::ApplyDamage(EnemyCharacter, DamageAmount, nullptr, this, nullptr);
			UE_LOG(LogTemp, Warning, TEXT("ApplyDamage called on: %s"), *EnemyCharacter->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor is not AAEnemyCharcter: %s"), *OtherActor->GetName());
		}
	}
	// Destroy the bullet after hitting something
	Destroy();
	
}


