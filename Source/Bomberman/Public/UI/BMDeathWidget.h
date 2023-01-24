// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BMDeathWidget.generated.h"

class UButton;

UCLASS()
class BOMBERMAN_API UBMDeathWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta=(BindWidget))
	UButton* MainMenuButton;

private:
	UFUNCTION()
	void RestartLevel();

	UFUNCTION()
	void OpenMainMenu();
};
