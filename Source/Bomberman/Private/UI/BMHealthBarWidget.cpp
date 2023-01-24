// Bomberman Test Project. 


#include "UI/BMHealthBarWidget.h"

#include "Player/BMPlayerCharacter.h"

void UBMHealthBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (HealthProgressBar)
	{
		const auto Player = Cast<ABMPlayerCharacter>(GetOwningPlayerPawn());
		if (!Player) return;

		const auto PlayerHealth = Cast<UBMHealthComponent>(
			Player->GetComponentByClass(UBMHealthComponent::StaticClass()));
		if (!PlayerHealth) return;

		PlayerHealth->OnHealthChanged.AddUObject(this, &UBMHealthBarWidget::OnHealthChanged);
		HealthProgressBar->SetPercent(PlayerHealth->GetHealthPercent());
	}
}

void UBMHealthBarWidget::OnHealthChanged(float Health)
{
	const auto Player = Cast<ABMPlayerCharacter>(GetOwningPlayerPawn());
	if (!Player) return;

	const auto PlayerHealth = Cast<UBMHealthComponent>(Player->GetComponentByClass(UBMHealthComponent::StaticClass()));
	if (!PlayerHealth) return;

	HealthProgressBar->SetPercent(PlayerHealth->GetHealthPercent());
}
