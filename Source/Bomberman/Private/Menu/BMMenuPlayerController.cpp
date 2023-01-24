// Bomberman Test Project. 


#include "Menu/BMMenuPlayerController.h"

void ABMMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
