// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BMAIController.generated.h"

class UBehaviorTree;
class UBMAIPerceptionComponent;

UCLASS()
class BOMBERMAN_API ABMAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABMAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBMAIPerceptionComponent* BMAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
