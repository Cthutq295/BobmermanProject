

#include "AIEnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AIEnemy.h"
#include "blackboard_keys.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboard_keys.h"
//#include "ai_tags.h"
#include "BombermanCharacter.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboard_keys.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"



AAIEnemyController::AAIEnemyController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/NPC_BT.NPC_BT'"));
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	setup_perception_system();
}

void AAIEnemyController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
	
}

void AAIEnemyController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}

}

UBlackboardComponent* AAIEnemyController::get_blackboard() const
{
	return blackboard;
}


void AAIEnemyController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	
	if(auto const ch = Cast<ABombermanCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

void AAIEnemyController::setup_perception_system()
{
	
		sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		sight_config->SightRadius = 500.0f;
		sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
		sight_config->PeripheralVisionAngleDegrees = 90.0f;
		sight_config->SetMaxAge(5.0f);
		sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		sight_config->DetectionByAffiliation.bDetectEnemies = true;
		sight_config->DetectionByAffiliation.bDetectFriendlies = true;
		sight_config->DetectionByAffiliation.bDetectNeutrals = true;

		// add sight configuration component to perception component
		GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIEnemyController::on_target_detected);
		GetPerceptionComponent()->ConfigureSense(*sight_config);

}



