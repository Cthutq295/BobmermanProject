// Bomberman Test Project. 


#include "UI/BMDeathWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBMDeathWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UBMDeathWidget::RestartLevel);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UBMDeathWidget::OpenMainMenu);
	}
}

void UBMDeathWidget::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, "Level1");
}

void UBMDeathWidget::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenuLevel");
}
