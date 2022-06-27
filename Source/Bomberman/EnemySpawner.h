// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemy.h"
#include "AIEnemyController.h"
#include "Engine/TriggerBox.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AEnemySpawner : public ATriggerBox
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIEnemy> Enemy;
	
	UFUNCTION()
	void SpawnEnemy();
	
protected:
	virtual void BeginPlay() override;
	
private:

	FTimerHandle timer;
	
};
