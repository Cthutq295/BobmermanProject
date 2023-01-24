// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "BMPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "BMPlayerState.generated.h"

UCLASS()
class BOMBERMAN_API ABMPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void ShowWinWidget(ABMPlayerController* Controller);
	void ShowDeathWidget(ABMPlayerController* Controller);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameWinWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameDeathWidgetClass;
	
};
