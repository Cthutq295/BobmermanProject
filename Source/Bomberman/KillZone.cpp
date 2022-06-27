// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"

#include "BombermanCharacter.h"
#include "BombermanGameMode.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AKillZone::AKillZone()
{
	
}

void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AKillZone::OnPlayerBeginOverlap);

	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true, -1,0,5);
	
}

void AKillZone::OnPlayerBeginOverlap(AActor* actor, AActor* ActorToKill)
{

	if (ActorToKill && ActorToKill != this && ActorToKill->GetClass()->GetName() == "ThirdPersonCharacter_C" )
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *ActorToKill->GetClass()->GetName()));
		ActorToKill->Destroy();
		ABombermanGameMode *GameMode = Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->ShowLoseWidget();
		
	} else if(ActorToKill && ActorToKill != this && ActorToKill->GetClass()->GetName() == "BP_AIEnemy_C" )
	{
		ActorToKill->Destroy();
	}
}
