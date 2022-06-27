#include "Wall.h"


AWall::AWall()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallBody"));
	

}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

