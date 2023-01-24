// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BMBombCooldownWidget.generated.h"

UCLASS()
class BOMBERMAN_API UBMBombCooldownWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* BombCooldownProgressBar;
	
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void GetCooldownPercent();
};
