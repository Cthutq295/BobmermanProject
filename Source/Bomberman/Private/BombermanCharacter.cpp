// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// ABombermanCharacter

ABombermanCharacter::ABombermanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	setup_stimulus();
}


void ABombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("PlaceBomb", IE_Released, this, &ABombermanCharacter::OnPlaceBomb);
	PlayerInputComponent->BindAction("LeaveGame", IE_Released, this, &ABombermanCharacter::OnLeaveGame);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABombermanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABombermanCharacter::MoveRight);

}

void ABombermanCharacter::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void ABombermanCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator YawRotation(0, 0, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, 0, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::OnPlaceBomb()
{
	if(IsReadyToPlaceBomb)
	{
		
		if(Bomb)
		{
			// draw line trace
			FHitResult OutHit;
			FVector Start = this->GetActorLocation();
			FVector DownVector = this->GetActorUpVector();
			FVector End = ((-DownVector * 400.0f)+Start);
			FCollisionQueryParams CollisionParams;

			bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

			if(isHit)
			{
				if(OutHit.bBlockingHit && OutHit.GetActor()->GetClass()->GetName() == "BP_TileFloor_C")
				{
					UWorld* const World = GetWorld();
					if(World)
					{
						IsReadyToPlaceBomb = false;
						FVector SpawnLocation = OutHit.GetActor()->GetActorLocation();
						SpawnLocation.Z = 50.0f;
						FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
						FActorSpawnParameters SpawnInfo;
						ABomb *SpawnBomb = World->SpawnActor<ABomb>(Bomb, SpawnLocation, SpawnRotation, SpawnInfo);
						GetWorldTimerManager().SetTimer(Timer, this, &ABombermanCharacter::ResetCoolDown, BombPlaceCoolDown, false);
					}
				}
			}
		}
	} 
}

void ABombermanCharacter::OnLeaveGame()
{
	
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("quit"));
	
}

void ABombermanCharacter::ResetCoolDown()
{
	IsReadyToPlaceBomb = true;
}
