// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelWinScreen.h"

#include "Kismet/KismetSystemLibrary.h"

void ULevelWinScreen::NativeConstruct()
{
	Super::NativeConstruct();
	BtnRestart->OnClicked.AddUniqueDynamic(this, &ULevelWinScreen::OnRestartLevel);
	BtnExit->OnClicked.AddUniqueDynamic(this, &ULevelWinScreen::OnExitLevel);

	
}

void ULevelWinScreen::OnRestartLevel()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World,TEXT("RestartLevel"));
	}
}

void ULevelWinScreen::OnExitLevel()
{
	UWorld* World = GetWorld();

	if(World)RemoveFromViewport();
	NativeDestruct();
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World,TEXT("quit"));
	}
}
