// Bomberman Test Project. 

#include "Triggers/TriggerFinishLevel.h"

#include "BMGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BMPlayerCharacter.h"
#include "Player/BMPlayerState.h"

ATriggerFinishLevel::ATriggerFinishLevel()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATriggerFinishLevel::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerFinishLevel::LevelFinish);
}

void ATriggerFinishLevel::LevelFinish(AActor* OverlappedActor, AActor* OtherActor)
{
	ABMPlayerCharacter* Player = Cast<ABMPlayerCharacter>(OtherActor);
	if (!Player) return;

	ABMPlayerState* State = Cast<ABMPlayerState>(Player->GetPlayerState());
	if(!State) return;

	State->ShowWinWidget(Cast<ABMPlayerController>(Player->GetController()));
	Player->Destroy();
}
