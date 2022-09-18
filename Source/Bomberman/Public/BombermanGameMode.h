// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameMode.generated.h"

UCLASS(minimalapi)
class ABombermanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	
	ABombermanGameMode();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LevelWinClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LevelLoseClass;

	UFUNCTION()
	void ShowWinWidget();

	UFUNCTION()
	void ShowLoseWidget();
};



