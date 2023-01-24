// Bomberman Test Project. 

#include "Player/BMPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Player/BMPlayerController.h"

void ABMPlayerState::ShowWinWidget(ABMPlayerController* Controller)
{
	UWorld* World = GetWorld();
	if (!World || !IsValid(GameWinWidgetClass)) return;

	UUserWidget* Widget = CreateWidget(World, GameWinWidgetClass);
	if (!Widget) return;

	Controller->SetInputMode(FInputModeUIOnly());
	Widget->AddToViewport();
	Controller->SetShowMouseCursor(true);
}

void ABMPlayerState::ShowDeathWidget(ABMPlayerController* Controller)
{
	UWorld* World = GetWorld();
	if (!World || !IsValid(GameDeathWidgetClass)) return;

	UUserWidget* Widget = CreateWidget(World, GameDeathWidgetClass);
	if (!Widget) return;

	Controller->SetInputMode(FInputModeUIOnly());
	Widget->AddToViewport();
	Controller->SetShowMouseCursor(true);
}
