// Bomberman Test Project. 


#include "Bomb/BMDamageZone.h"

#include "DrawDebugHelpers.h"
#include "Player/BMBaseCharacter.h"

void ABMDamageZone::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true);
	OnActorBeginOverlap.AddDynamic(this, &ABMDamageZone::OnComponentBeginOverlap);
}

void ABMDamageZone::OnComponentBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == this) return;
	ABMBaseCharacter* Player = Cast<ABMBaseCharacter>(OtherActor);
	if (Player)
	{
		// TODO Change this to a proper death.
		Player->Destroy();
		return;
	}
}

void ABMDamageZone::SetDamageAmount(float Damage)
{
	DamageAmount = Damage;
}