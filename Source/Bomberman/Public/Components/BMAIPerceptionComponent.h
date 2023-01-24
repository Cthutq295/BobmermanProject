// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "BMAIPerceptionComponent.generated.h"

UCLASS()
class BOMBERMAN_API UBMAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetClosestEnemy();
};
