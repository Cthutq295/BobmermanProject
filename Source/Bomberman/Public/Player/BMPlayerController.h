// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BMPlayerController.generated.h"

UCLASS()
class BOMBERMAN_API ABMPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	void ExitGame();
	void RestartLevel();
	
};
