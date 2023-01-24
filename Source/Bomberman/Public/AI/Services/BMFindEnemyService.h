// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BMFindEnemyService.generated.h"

UCLASS()
class BOMBERMAN_API UBMFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UBMFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
