// Bomberman Test Project. 

#include "UI/BMGameHUD.h"

#include "Blueprint/UserWidget.h"

void ABMGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerHUDWidgetClass)
	{
		const auto PlayerHUDWidget = CreateWidget(GetWorld(), PlayerHUDWidgetClass);
		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
}
