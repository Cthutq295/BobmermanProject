// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Player/BMBaseCharacter.h"
#include "BMAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class BOMBERMAN_API ABMAICharacter : public ABMBaseCharacter
{
	GENERATED_BODY()
public:
	ABMAICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	UBoxComponent* DamageBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int DamageAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageRate = 0.20f;

	virtual void OnDeath() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStartTouchEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndTouchEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex);

private:
	FTimerHandle DamageTimerHandle;

	UPROPERTY()
	ABMBaseCharacter* Enemy = nullptr;

	void ApplyDamageToEnemy();
};
