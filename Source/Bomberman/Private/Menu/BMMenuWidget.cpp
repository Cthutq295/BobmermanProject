// Bomberman Test Project. 


#include "Menu/BMMenuWidget.h"

#include "BMGameInstance.h"
#include "Bomberman/BMUtils.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UBMMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SizeXEditableText)
	{
		SizeXEditableText->SetText(FText::FromString(FString::FromInt(SizeX)));
		SizeXEditableText->OnTextCommitted.AddDynamic(this, &UBMMenuWidget::OnXSizeTextChanged);
	}
	if (SizeYEditableText)
	{
		SizeYEditableText->SetText(FText::FromString(FString::FromInt(SizeY)));
		SizeYEditableText->OnTextCommitted.AddDynamic(this, &UBMMenuWidget::OnYSizeTextChanged);
	}

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UBMMenuWidget::StartGame);
	}
	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UBMMenuWidget::ExitGame);
	}
}

void UBMMenuWidget::OnXSizeTextChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (!Text.IsNumeric()) SizeXEditableText->SetText(FText::FromString(FString::FromInt(SizeX)));
	else
	{
		int32 const NewSize = FMath::Clamp(FCString::Atoi(*Text.ToString()), BMUtils::MinMapSize, BMUtils::MaxMapSize);
		SizeXEditableText->SetText(FText::FromString(FString::FromInt(NewSize)));
		const auto GameInstance = Cast<UBMGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SetMapSizeX(NewSize);
		}
	}
}

void UBMMenuWidget::OnYSizeTextChanged(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (!Text.IsNumeric()) SizeYEditableText->SetText(FText::FromString(FString::FromInt(SizeX)));
	else
	{
		int32 const NewSize = FMath::Clamp(FCString::Atoi(*Text.ToString()), BMUtils::MinMapSize, BMUtils::MaxMapSize);
		SizeYEditableText->SetText(FText::FromString(FString::FromInt(NewSize)));
		const auto GameInstance = Cast<UBMGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SetMapSizeY(NewSize);
		}
	}
}

void UBMMenuWidget::StartGame()
{
	UGameplayStatics::OpenLevel(this, "Level1");
}

void UBMMenuWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
