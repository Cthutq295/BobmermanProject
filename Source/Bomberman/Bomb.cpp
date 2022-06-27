


//#include "DrawDebugHelpers.h"
#include "Bomb.h"

#include "Kismet/GameplayStatics.h"


ABomb::ABomb()
{

	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;
	
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombBody"));
	BombMesh->SetupAttachment(SceneComponent);
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
	BombMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CheckTilesToBomb();
}

void ABomb::CheckTilesToBomb()
{
	FHitResult OutHit;
	FVector Start = this->GetActorLocation();
	FVector ActorDownVector = this->GetActorUpVector();
	FVector End = ((ActorDownVector * 400.0f) + Start);
	FCollisionQueryParams CollisionParams;

	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
//	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);

	if(isHit)
	{
		if(OutHit.bBlockingHit && OutHit.GetActor()->GetClass()->GetName() == "BP_TileFloor_C")
		{
			
			// Central Tile
			DetectedTiles.Push(Cast<ATile>(OutHit.GetActor()));

			ATile *TileToCheck;
			
			// Forward Direction Tiles
			for(int i = 0; i < 2; i++)
			{
				Start.X += 200;
				isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
				TileToCheck = Cast<ATile>(OutHit.GetActor());
				if(TileToCheck->IsBlocked) break;
			//	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
			//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				DetectedTiles.Push(Cast<ATile>(OutHit.GetActor()));
			}
			Start = this->GetActorLocation();
			// Backward Direction Tiles
			for(int i = 0; i < 2; i++)
			{
				Start.X -= 200;
				isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
				TileToCheck = Cast<ATile>(OutHit.GetActor());
				if(TileToCheck->IsBlocked) break;
			//	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
			//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				DetectedTiles.Push(Cast<ATile>(OutHit.GetActor()));
			}
			Start = this->GetActorLocation();
			// Left Direction Tiles
			for(int i = 0; i < 2; i++)
			{
				Start.Y += 200;
				isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
				TileToCheck = Cast<ATile>(OutHit.GetActor());
				if(TileToCheck->IsBlocked) break;
			//	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
			//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				DetectedTiles.Push(Cast<ATile>(OutHit.GetActor()));
			}
			Start = this->GetActorLocation();
			// Right direction Tiles
			for(int i = 0; i < 2; i++)
			{
				Start.Y -= 200;
				isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
				TileToCheck = Cast<ATile>(OutHit.GetActor());
				if(TileToCheck->IsBlocked) break;
			//	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
			//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				DetectedTiles.Push(Cast<ATile>(OutHit.GetActor()));
			}
			GetWorldTimerManager().SetTimer(TimerHandler, this, &ABomb::DoExplosion, ExplodeTime, false);
			
		}
	}
}

void ABomb::DoExplosion()
{
	FVector TileLocation;
	UWorld* const World = GetWorld();
	TArray<AKillZone*> KillZoneList;

	if(ExplodeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, GetActorLocation());
	}
	
	for(ATile *Tile: DetectedTiles )
	{
		if(Tile != nullptr)
		{
			TileLocation = Tile->GetActorLocation();
			TileLocation.Z +=200;
			FActorSpawnParameters SpawnInfo;
			AKillZone *KillZone = World->SpawnActor<AKillZone>(KillBox,TileLocation, Tile->GetActorRotation(), SpawnInfo);
			KillZoneList.Push(KillZone);
			
			if(Tile->WallMesh)
			{
				Tile->WallMesh->DestroyComponent();
				Tile->HasWall = false;
			}

			if(ExplodeParticle)
			{
				TileLocation.Z +=100;
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, TileLocation);
				
			}
		}
		
	}
	
	this->Destroy();
}

