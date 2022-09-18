#include "Tile.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileBody"));
	TileMesh->SetupAttachment(SceneComponent);

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallBody"));
	WallMesh->SetupAttachment(SceneComponent);

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockBody"));
	BlockMesh->SetupAttachment(SceneComponent);
}


void ATile::BeginPlay()
{
	Super::BeginPlay();
	GenerateWalls();
}

void ATile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	// We don't want to draw mesh in editor when we don't want it to be spawned in game.
	if(!HasWall) WallMesh->SetVisibility(false);
	else WallMesh->SetVisibility(true);
	
	if(!IsBlocked) BlockMesh->SetVisibility(false);
	else BlockMesh->SetVisibility(true);
}

void ATile::GenerateWalls()
{

	if(IsBlocked) WallMesh->DestroyComponent();
	else BlockMesh->DestroyComponent();
	
	if(HasWall == false)
	{
		if(WallMesh)
		{
			WallMesh->DestroyComponent();
		}
	}

	if(HasWall)
	{
		int WallSpawnChance = FMath::RandRange(0,10);
		if(WallSpawnChance > 5)
		{
			WallMesh->DestroyComponent();
			HasWall = false;
		}
	}
}

