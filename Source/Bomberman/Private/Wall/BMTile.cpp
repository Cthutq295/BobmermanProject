// Bomberman Test Project. 

#include "Wall/BMTile.h"

ABMTile::ABMTile()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("TileMeshComponent");
	TileMesh->SetupAttachment(GetRootComponent());

	BreakableWallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BreakableWallMeshComponent");
	BreakableWallMesh->SetupAttachment(GetRootComponent());

	UnbreakableWallMesh = CreateDefaultSubobject<UStaticMeshComponent>("UnbreakableWallMeshComponent");
	UnbreakableWallMesh->SetupAttachment(GetRootComponent());
}

void ABMTile::BeginPlay()
{
	Super::BeginPlay();
	GenerateWall();
}

void ABMTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	switch (WallType)
	{
	case EWallType::None:
		BreakableWallMesh->SetVisibility(false);
		UnbreakableWallMesh->SetVisibility(false);
		break;
	case EWallType::Random:
		UnbreakableWallMesh->SetVisibility(false);
		BreakableWallMesh->SetVisibility(true);
		break;
	case EWallType::Breakable:
		UnbreakableWallMesh->SetVisibility(false);
		BreakableWallMesh->SetVisibility(true);
		break;
	case EWallType::Unbreakable:
		BreakableWallMesh->SetVisibility(false);
		UnbreakableWallMesh->SetVisibility(true);
		break;
	default:
		BreakableWallMesh->SetVisibility(false);
		UnbreakableWallMesh->SetVisibility(false);
		break;
	}
}

void ABMTile::GenerateWall()
{
	switch (WallType)
	{
	case EWallType::None:
		BreakableWallMesh->DestroyComponent();
		UnbreakableWallMesh->DestroyComponent();
		break;
	case EWallType::Random:
		UnbreakableWallMesh->DestroyComponent();
		break;
	case EWallType::Breakable:
		UnbreakableWallMesh->DestroyComponent();
		break;
	case EWallType::Unbreakable:
		BreakableWallMesh->DestroyComponent();
		break;
	default:
		break;
	}

	if (BreakableWallMesh && WallType == EWallType::Random)
	{
		if (FMath::FRandRange(0.0, 1.0) >= Threshold)
		{
			BreakableWallMesh->DestroyComponent();
		}
	}
}

void ABMTile::DestroyWall()
{
	// TODO Add Effects for destroyment;
	if (BreakableWallMesh)
	{
		BreakableWallMesh->DestroyComponent();
	}
}

void ABMTile::SetThreshold(float NewThreshold)
{
	Threshold = NewThreshold;
}
