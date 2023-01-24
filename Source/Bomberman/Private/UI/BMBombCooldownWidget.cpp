// Bomberman Test Project. 


#include "UI/BMBombCooldownWidget.h"

#include "Player/BMPlayerCharacter.h"

void UBMBombCooldownWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBMBombCooldownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(BombCooldownProgressBar) GetCooldownPercent();
}

void UBMBombCooldownWidget::GetCooldownPercent()
{
	const auto Player = Cast<ABMPlayerCharacter>(GetOwningPlayerPawn());
	if(!Player) return;
	BombCooldownProgressBar->SetPercent( Player->GetBombCooldownPercent());
}
