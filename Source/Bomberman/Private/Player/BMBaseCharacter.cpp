// Bomberman Test Project. 

#include "Player/BMBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABMBaseCharacter::ABMBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UBMHealthComponent>("HealthComponent");

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ABMBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddUObject(this, &ABMBaseCharacter::OnDeath);
}

void ABMBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(RagdollTimeExistence);
	GetCapsuleComponent()->SetCollisionResponseToChannels(ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GetMesh()->SetSimulatePhysics(true);
}

void ABMBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
