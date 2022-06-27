// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "LevelWinScreen.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ULevelWinScreen : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton * BtnRestart;
	UPROPERTY(meta = (BindWidget))
	UButton * BtnExit;

	UFUNCTION()
	void OnRestartLevel();

	UFUNCTION()
	void OnExitLevel();
	
};
