// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BMGameHUD.generated.h"

UCLASS()
class BOMBERMAN_API ABMGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;
};
