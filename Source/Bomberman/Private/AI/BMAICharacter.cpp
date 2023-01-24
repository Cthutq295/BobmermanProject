// Bomberman Test Project. 


#include "AI/BMAICharacter.h"

#include "AI/BMAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BMPlayerCharacter.h"
#include "Player/BMPlayerState.h"

ABMAICharacter::ABMAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ABMAIController::StaticClass();

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	DamageBox = CreateDefaultSubobject<UBoxComponent>("DamageBoxComponent");
	DamageBox->SetupAttachment(GetRootComponent());
}

void ABMAICharacter::OnDeath()
{
	Super::OnDeath();
	DamageBox->DestroyComponent();
}

void ABMAICharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterType = ECharacterType::NPC;

	DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ABMAICharacter::OnStartTouchEnemy);
	DamageBox->OnComponentEndOverlap.AddDynamic(this, &ABMAICharacter::OnEndTouchEnemy);
}

void ABMAICharacter::OnStartTouchEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	ABMPlayerCharacter* Player = Cast<ABMPlayerCharacter>(OtherActor);
	if (Player)
	{
		Enemy = Player;
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ABMAICharacter::ApplyDamageToEnemy, DamageRate, true);
	}
}

void ABMAICharacter::OnEndTouchEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABMPlayerCharacter* Player = Cast<ABMPlayerCharacter>(OtherActor);
	if (Player)
	{
		Enemy = nullptr;
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	}
}

void ABMAICharacter::ApplyDamageToEnemy()
{
	if (Enemy)
		UGameplayStatics::ApplyDamage(Enemy, DamageAmount, nullptr, this, nullptr);
}
