// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BMMenuWidget.generated.h"

class UEditableText;
class UButton;

UCLASS()
class BOMBERMAN_API UBMMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UEditableText* SizeXEditableText;

	UPROPERTY(meta=(BindWidget))
	UEditableText* SizeYEditableText;

	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ExitGameButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = 7, ClampMax = 30))
	int32 SizeX = 7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = 7, ClampMax = 30))
	int32 SizeY = 7;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnXSizeTextChanged(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnYSizeTextChanged(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void ExitGame();
};
