// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BMPlayerHUDWidget.generated.h"

UCLASS()
class BOMBERMAN_API UBMPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
};
