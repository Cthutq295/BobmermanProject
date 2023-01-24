// Bomberman Test Project. 


#include "UI/BMGameWinWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBMGameWinWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UBMGameWinWidget::RestartLevel);
	}

	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UBMGameWinWidget::OpenMainMenu);
	}
}

void UBMGameWinWidget::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, "Level1");
}

void UBMGameWinWidget::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenuLevel");
}
