// Copyright Epic Games, Inc. All Rights Reserved


#include "Bullets.h"

// Sets default values
ABullets::ABullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up projectile movement component
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	BulletMovement->InitialSpeed = 6000.0f;
	BulletMovement->MaxSpeed = 6000.0f;
	BulletMovement->ProjectileGravityScale = 0.0f;//No gravity

	//Set up for static mesh component
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	RootComponent = BulletMesh;
	//Setup Collision to detect overlaps
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	BulletMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BulletMesh->SetSimulatePhysics(true);

	//Binding the OnHit function to the Hit event
	BulletMesh->OnComponentHit.AddDynamic(this, &ABullets::OnHit);

	
	

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

//Setting up the OnHit Function
void ABullets::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//Check if the bullet hit a valid target
	if (OtherActor && OtherActor != this && OtherComp)
	{
		//Apply damage to the hit actor
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, GetInstigatorController(), this, nullptr);
		//Destroy the bullet after hitting 
		Destroy();
	}
}
