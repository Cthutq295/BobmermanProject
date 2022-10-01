// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"

#include "AIEnemy.h"
#include "BombermanCharacter.h"
#include "BombermanGameMode.h"
#include "Kismet/GameplayStatics.h"

void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AKillZone::OnPlayerBeginOverlap);
}

void AKillZone::OnPlayerBeginOverlap(AActor* actor, AActor* ActorToKill)
{
	if (ActorToKill == this) return;

	ABombermanCharacter* Player = Cast<ABombermanCharacter>(ActorToKill);
	
	if (Player)
	{
		ActorToKill->Destroy();
		ABombermanGameMode* GameMode = Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->ShowLoseWidget();
		return;
	}

	AAIEnemy* EnemyBot = Cast<AAIEnemy>(ActorToKill);
	
	if (EnemyBot) ActorToKill->Destroy();
}
