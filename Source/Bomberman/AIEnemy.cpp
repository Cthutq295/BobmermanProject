

#include "AIEnemy.h"

#include "BombermanGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


AAIEnemy::AAIEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}


void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();


	this->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAIEnemy::OnHit);
	UMaterialInstanceDynamic * material = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this );

	if(material)
	{
		material->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f,0.0f, 1.0f));
		GetMesh()->SetMaterial(0,material);
	}
	
}


void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AAIEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* player, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
		
	if (player && player != this && player->GetClass()->GetName() == "ThirdPersonCharacter_C" )
	{
		player->Destroy();
		ABombermanGameMode *GameMode = Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->ShowLoseWidget();
		this->Destroy();
	}
}

