// Bomberman Test Project. 


#include "Player/BMPlayerController.h"

#include "Kismet/GameplayStatics.h"

void ABMPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ABMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ExitGame", IE_Pressed, this, &ABMPlayerController::ExitGame);
	InputComponent->BindAction("RestartGame", IE_Pressed, this, &ABMPlayerController::RestartLevel);
}

void ABMPlayerController::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
}

void ABMPlayerController::RestartLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}
