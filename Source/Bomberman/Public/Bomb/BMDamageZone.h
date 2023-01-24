// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BMDamageZone.generated.h"

UCLASS()
class BOMBERMAN_API ABMDamageZone : public ATriggerBox
{
	GENERATED_BODY()
public:
	void SetDamageAmount(float Damage);
	
protected:
	virtual void BeginPlay() override;


private:
	float DamageAmount = 0.0f;
	
	UFUNCTION()
	void OnComponentBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
