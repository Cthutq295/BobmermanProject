// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "KillZone.generated.h"

UCLASS()
class BOMBERMAN_API AKillZone : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	AKillZone();
	virtual void BeginPlay();

	UFUNCTION()
	void OnPlayerBeginOverlap(AActor *actor, AActor* otherActor);
	
};
