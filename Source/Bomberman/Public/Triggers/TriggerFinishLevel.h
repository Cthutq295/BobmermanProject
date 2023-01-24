// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerFinishLevel.generated.h"

UCLASS()
class BOMBERMAN_API ATriggerFinishLevel : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATriggerFinishLevel();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void LevelFinish(AActor* OverlappedActor, AActor* OtherActor);
};
