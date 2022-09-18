// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BombermanGameMode.h"
#include "Engine/TriggerBox.h"
#include "MapFinish.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AMapFinish : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	//TSubclassOf<UUserWidget> LevelWinClass;

	ABombermanGameMode *GameMode;
	
	UFUNCTION()
	void OnPlayerBeginOverlap(AActor *actor, AActor* otherActor);
	
};
