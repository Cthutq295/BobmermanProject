// Bomberman Test Project. 


#include "Components/BMHealthComponent.h"

UBMHealthComponent::UBMHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBMHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (Owner) Owner->OnTakeAnyDamage.AddDynamic(this, &UBMHealthComponent::OnTakeAnyDamage);
	Health = MaxHealth;
}

void UBMHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, 1000.f);
	OnHealthChanged.Broadcast(Health);

	if (FMath::IsNearlyZero(Health))
	{
		OnDeath.Broadcast();
		Health = 0.0f;
	}
}