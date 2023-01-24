// Bomberman Test Project. 


#include "AI/BMAIController.h"

#include "AI/BMAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BMAIPerceptionComponent.h"

ABMAIController::ABMAIController()
{
	BMAIPerceptionComponent = CreateDefaultSubobject<UBMAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*BMAIPerceptionComponent);
	bWantsPlayerState = true;
}

void ABMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto BMCharacter = Cast<ABMAICharacter>(InPawn);
	if (BMCharacter)
	{
		RunBehaviorTree(BMCharacter->BehaviorTreeAsset);
	}
}

void ABMAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ABMAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
