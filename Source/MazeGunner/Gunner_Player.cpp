// Fill out your copyright notice in the Description page of Project Settings.


#include "Gunner_Player.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AGunner_Player::AGunner_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setting the max walk speed of the player
	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	//Enabling Crouching
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	//Enables the rotation to matach the movement 
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	

	//Setting up the Camera Component
	Gunner_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Gunner_Camera"));
	Gunner_Camera->SetupAttachment(RootComponent);
	Gunner_Camera->SetRelativeLocation(FVector(10.0f, 0.0f, 110.0f));
	Gunner_Camera->bUsePawnControlRotation = true;

	//Setting up the weapon mesh
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	//"ik_hand_r_gun_socket"

	WeaponMesh->SetupAttachment(GetMesh(), TEXT("ik_hand_r_gun_socket"));



}

// Called when the game starts or when spawned
void AGunner_Player::BeginPlay()
{
	Super::BeginPlay();

	//Assign the custom animation instance
	if (USkeletalMeshComponent* SkeletalMesh = GetMesh())
	{
		UGunner_Animation* AnimInstance = Cast<UGunner_Animation>(SkeletalMesh->GetAnimInstance());
		if (AnimInstance)
		{
			MyAnimInstance = AnimInstance;
		}
	}

}

// Called every frame
void AGunner_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyAnimInstance)
		{
			// Update Speed
			FVector Velocity = GetVelocity();
			float Speed = Velocity.Size();
			MyAnimInstance->speed = Speed;

			// Update Running State
			MyAnimInstance->bIsRunning = (Speed >= 600.0f);
		}
	//Smoothly interpolate the camera position based on the crouch state
	FVector TargetPosition = FMath::Lerp(StandingCameraPosition, CrouchingCameraPosition, CameraTransitionAlpha);
	Gunner_Camera->SetRelativeLocation(TargetPosition);

	


}

// Called to bind functionality to input
void AGunner_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding input actions with axis mappings
	PlayerInputComponent->BindAxis("MoveForward", this, &AGunner_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGunner_Player::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AGunner_Player::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AGunner_Player::AddControllerPitchInput);

	//Binding input actions with action mappings
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AGunner_Player::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AGunner_Player::StopSprinting);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGunner_Player::StartJumping);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGunner_Player::StopJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AGunner_Player::ImCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AGunner_Player::NotCrouch);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AGunner_Player::Interact);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGunner_Player::FireWeapon);
}
void AGunner_Player::ImCrouch() {
	//Sets the player to crouching
	Crouch();
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	//Sets the players camera to a lower position
	//Gunner_Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 45.0f));
	CameraTransitionAlpha = FMath::Clamp(CameraTransitionAlpha + CameraTransitionSpeed * GetWorld()->GetDeltaSeconds(), 0.0f, 1.0f);
}

void AGunner_Player::NotCrouch() {
	UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	//Gunner_Camera->SetRelativeLocation(FVector(10.0f, 0.0f, 100.0f));
	CameraTransitionAlpha = FMath::Clamp(CameraTransitionAlpha - CameraTransitionSpeed * GetWorld()->GetDeltaSeconds(), 0.0f, 1.0f);
}
void AGunner_Player::MoveForward(float input_value) {
	// We are moving the player forward
	AddMovementInput(GetActorForwardVector(), input_value);
}

void AGunner_Player::MoveRight(float input_value) {
	//Moving the player right
	AddMovementInput(GetActorRightVector(), input_value);
}

void AGunner_Player::StartSprinting() {
	GetCharacterMovement()->MaxWalkSpeed = 1200.f;

}
void AGunner_Player::StopSprinting() {
	GetCharacterMovement() -> MaxWalkSpeed = 600.f;
}

void AGunner_Player::StartJumping() {
	//Sets the player to jumping
	bPressedJump = true;


}

void AGunner_Player::StopJump() {
	//Sets the player stop jumping
	bPressedJump = false;
}

void AGunner_Player::Interact() {
	//Check if the player is overlapping with a pickup item
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->IsA(AAPickupItem::StaticClass()))
		{
			AAPickupItem* PickupItem = Cast<AAPickupItem>(Actor);
			if (PickupItem)
			{
				PickupItem->AttachToCharacter();
				PickupItem->OnPickup();
				break;
			}
		}
	}
}

//Function to fire the weapon

void AGunner_Player::FireWeapon()
{
	if (!BulletClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("BulletClass is not set!"));
		return;
	}
	if (!WeaponMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponMesh is not set!"));
		return;
	}

	//Get the MuzzleSockeet Location and rotation
	FVector MuzzleLocation = WeaponMesh->GetSocketLocation(TEXT("MuzzleSocket"));
	FRotator MuzzleRotation = WeaponMesh->GetSocketRotation(TEXT("MuzzleSocket"));

	//Spawn the bullet
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	ABullets* Bullet = GetWorld()->SpawnActor<ABullets>(BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (Bullet)
	{
		//Set the bullet's velocity
		FVector LaunchDirection = MuzzleRotation.Vector();
		Bullet->BulletMovement->SetVelocityInLocalSpace(LaunchDirection * Bullet->BulletMovement->InitialSpeed);
		Bullet->BulletMovement->Activate();

	}
	UE_LOG(LogTemp, Warning, TEXT("Fireweapon called!"));
	UE_LOG(LogTemp, Warning, TEXT("MuzzleLocation: %s"), *MuzzleLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("MuzzleRotation: %s"), *MuzzleRotation.ToString());
	
	
}

