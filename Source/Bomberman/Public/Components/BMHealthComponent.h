// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BMHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOMBERMAN_API UBMHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBMHealthComponent();

	float GetHealthPercent() const { return Health / MaxHealth; }
	float GetHealth() const { return Health; }

	bool IsDead() const { return FMath::IsNearlyZero(Health) ? true : false; }

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta=(ClampMin = 1.0f))
	float MaxHealth = 100.f;

	virtual void BeginPlay() override;

private:
	float Health;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);
};
