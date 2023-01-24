// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BMGameInstance.h"
#include "AI/BMAICharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Player/BMPlayerCharacter.h"
#include "Wall/BMTile.h"
#include "BMGameModeBase.generated.h"

UCLASS()
class BOMBERMAN_API ABMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABMGameModeBase();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = 1, ClampMax = 20), Category = "Spawn")
	int32 EnemySpawnAmount = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ABMTile> TileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ABMPlayerCharacter> PlayerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ABMAICharacter> EnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ATriggerBox> TriggerFinishClass;

private:
	UPROPERTY()
	const UBMGameInstance* GameInstance;

	UPROPERTY()
	TArray<ABMTile*> TileList;

	UPROPERTY()
	ATriggerBox* TriggerFinish = nullptr;

	void GenerateTiles();
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnTriggerFinish();
};
