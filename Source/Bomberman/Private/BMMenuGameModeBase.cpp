// Bomberman Test Project. 


#include "BMMenuGameModeBase.h"

#include "Menu/BMMainMenuHUD.h"
#include "Menu/BMMenuPlayerController.h"

ABMMenuGameModeBase::ABMMenuGameModeBase()
{
	PlayerControllerClass = ABMMenuPlayerController::StaticClass();
	HUDClass = ABMMainMenuHUD::StaticClass();
}
