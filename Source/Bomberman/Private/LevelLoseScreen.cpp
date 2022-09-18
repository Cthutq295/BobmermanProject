
#include "LevelLoseScreen.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void ULevelLoseScreen::NativeConstruct()
{
	Super::NativeConstruct();

	BtnRestart->OnClicked.AddUniqueDynamic(this, &ULevelLoseScreen::OnRestartLevel);
	BtnExit->OnClicked.AddUniqueDynamic(this, &ULevelLoseScreen::OnExitLevel);
}

void ULevelLoseScreen::OnRestartLevel()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World,TEXT("RestartLevel"));
	}
}

void ULevelLoseScreen::OnExitLevel()
{
	UWorld* World = GetWorld();

	if(World)RemoveFromViewport();
	NativeDestruct();
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World,TEXT("quit"));
	}
}
