// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BMHealthBarWidget.generated.h"

UCLASS()
class BOMBERMAN_API UBMHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnHealthChanged(float Health);
};
