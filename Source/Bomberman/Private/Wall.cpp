#include "Wall.h"

AWall::AWall()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallBody"));
	

}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}


