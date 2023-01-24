// Bomberman Test Project. 

#include "DrawDebugHelpers.h"
#include "Bomb/BMBomb.h"
#include "Kismet/GameplayStatics.h"

ABMBomb::ABMBomb()
{
	PrimaryActorTick.bCanEverTick = false;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BombMesh");
	RootComponent = BombMesh;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(GetRootComponent());
}

void ABMBomb::SetOccupiedTile(ABMTile* Tile)
{
	OccupiedTile = Tile;
	TilesToBomb.Push(OccupiedTile);
}

void ABMBomb::BeginPlay()
{
	Super::BeginPlay();

	BombMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FindNeighborTiles();
	GetWorldTimerManager().SetTimer(BombExplodeTimerHandle, this, &ABMBomb::Explode, ExplodeTime, false);
}

void ABMBomb::FindNeighborTiles()
{
	if (!GetWorld()) return;

	float const TraceDistance = 400.f;
	float const TraceZOffset = 100.f;

	FVector TraceStart = GetActorLocation();
	TraceStart.Z += TraceZOffset;
	const FVector TraceDirection = -GetActorUpVector();
	FVector TraceEnd = TraceStart + TraceDirection * TraceDistance;

	FHitResult HitResult;

	ABMTile* Tile = nullptr;

	// Forward direction.
	const float NextTileLocationOffset = 200.f;
	for (int i = 0; i < ExplodeRadiusXDirection - 1; ++i)
	{
		TraceStart.X += NextTileLocationOffset;
		TraceEnd.X += NextTileLocationOffset;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.bBlockingHit) Tile = Cast<ABMTile>(HitResult.Actor);
		if (!Tile) continue;
		if (Tile->GetWallType() == EWallType::Unbreakable) break;

		TilesToBomb.Push(Tile);
	}

	TraceStart = GetActorLocation();
	TraceStart.Z += TraceZOffset;
	TraceEnd = TraceStart + TraceDirection * TraceDistance;

	// Backward direction.
	for (int i = 0; i < ExplodeRadiusXDirection - 1; ++i)
	{
		TraceStart.X -= NextTileLocationOffset;
		TraceEnd.X -= NextTileLocationOffset;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.bBlockingHit) Tile = Cast<ABMTile>(HitResult.Actor);
		if (!Tile) continue;
		if (Tile->GetWallType() == EWallType::Unbreakable) break;

		TilesToBomb.Push(Tile);
	}

	TraceStart = GetActorLocation();
	TraceStart.Z += TraceZOffset;
	TraceEnd = TraceStart + TraceDirection * TraceDistance;

	// Left direction.
	for (int i = 0; i < ExplodeRadiusYDirection - 1; ++i)
	{
		TraceStart.Y += NextTileLocationOffset;
		TraceEnd.Y += NextTileLocationOffset;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.bBlockingHit) Tile = Cast<ABMTile>(HitResult.Actor);
		if (!Tile) continue;
		if (Tile->GetWallType() == EWallType::Unbreakable) break;

		TilesToBomb.Push(Tile);
	}

	TraceStart = GetActorLocation();
	TraceStart.Z += TraceZOffset;
	TraceEnd = TraceStart + TraceDirection * TraceDistance;

	// Right direction.
	for (int i = 0; i < ExplodeRadiusYDirection - 1; ++i)
	{
		TraceStart.Y -= NextTileLocationOffset;
		TraceEnd.Y -= NextTileLocationOffset;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.bBlockingHit) Tile = Cast<ABMTile>(HitResult.Actor);
		if (!Tile) continue;
		if (Tile->GetWallType() == EWallType::Unbreakable) break;

		TilesToBomb.Push(Tile);
	}
}

void ABMBomb::Explode()
{
	for (ABMTile* Tile : TilesToBomb)
	{
		if (!Tile) continue;
		Tile->DestroyWall();
	}
	
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		DamageAmount,
		GetActorLocation(),
		200 * ExplodeRadiusXDirection,
		nullptr,
		{},
		this,
		nullptr,
		DuFullDamage);

	RadialForceComponent->Radius = ExplodeRadiusXDirection * 200;
	RadialForceComponent->FireImpulse();	
	
	if (OccupiedTile)
	{
		OccupiedTile->HasBomb = false;
	}
	Destroy();
}
