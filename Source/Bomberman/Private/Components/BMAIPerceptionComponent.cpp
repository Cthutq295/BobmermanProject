// Bomberman Test Project. 


#include "Components/BMAIPerceptionComponent.h"

#include "AIController.h"
#include "Bomberman/BMUtils.h"
#include "Components/BMHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Sight.h"

AActor* UBMAIPerceptionComponent::GetClosestEnemy()
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PerceiveActor : PerceiveActors)
	{
		const auto HealthComponent = PerceiveActor->FindComponentByClass<UBMHealthComponent>();

		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		const auto AreEnemies = PerceivePawn && BMUtils::AreEnemies(Controller, PerceivePawn->Controller);

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceiveActor;
			}
		}
	}

	return BestPawn;
}
