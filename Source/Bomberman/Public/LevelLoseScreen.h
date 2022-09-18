// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelLoseScreen.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ULevelLoseScreen : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnRestart;
	UPROPERTY(meta = (BindWidget))
	UButton* BtnExit;

	UFUNCTION()
	void OnRestartLevel();

	UFUNCTION()
	void OnExitLevel();
	
};
