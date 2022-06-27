// Copyright Epic Games, Inc. All Rights Reserved.

#include "BombermanGameMode.h"
#include "BombermanCharacter.h"
#include "NavigationSystem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABombermanGameMode::ABombermanGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABombermanGameMode::BeginPlay()
{
	Super::BeginPlay();


}

void ABombermanGameMode::ShowWinWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWorld* World = GetWorld();
	if(IsValid(LevelWinClass))
	{
		UUserWidget *Widget = CreateWidget(World, LevelWinClass);
		if(Widget)
		{
			Widget->AddToViewport();
			Controller->SetShowMouseCursor(true);
		}
	}  

}

void ABombermanGameMode::ShowLoseWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWorld* World = GetWorld();
	if(IsValid(LevelLoseClass))
	{
		UUserWidget *Widget = CreateWidget(World, LevelLoseClass);
		if(Widget)
		{
			Widget->AddToViewport();
			Controller->SetShowMouseCursor(true);
		}
	}
}
