// Bomberman Test Project. 

#include "Menu/BMMainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ABMMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}
