// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BMMainMenuHUD.generated.h"

UCLASS()
class BOMBERMAN_API ABMMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void BeginPlay() override;
};
