// Copyright Epic Games, Inc. All Rights Reserved.

#include "BMGameModeBase.h"
#include "AI/BMAICharacter.h"
#include "AI/BMAIController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BMPlayerCharacter.h"
#include "Player/BMPlayerController.h"
#include "Player/BMPlayerState.h"
#include "UI/BMGameHUD.h"

ABMGameModeBase::ABMGameModeBase()
{
	DefaultPawnClass = ABMBaseCharacter::StaticClass();
	PlayerControllerClass = ABMPlayerController::StaticClass();
	PlayerStateClass = ABMPlayerState::StaticClass();
	HUDClass = ABMGameHUD::StaticClass();
}

void ABMGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UBMGameInstance>(GetWorld()->GetGameInstance());

	GenerateTiles();
	SpawnPlayer();
	SpawnEnemy();
	SpawnTriggerFinish();
}

void ABMGameModeBase::GenerateTiles()
{
	const auto World = GetWorld();
	if (!World) return;

	if (!GameInstance) return;

	int32 const StepShift = 200;
	FVector SpawnedTileLocation = FVector::ZeroVector;

	// The far we from player spawn, the less walls will be generated, so AI's are not stuck at their spawn.
	float Threshold = 0.9f;

	for (int i = 0; i < GameInstance->GetMapSizeX(); ++i)
	{
		for (int j = 0; j < GameInstance->GetMapSizeY(); ++j)
		{
			ABMTile* Tile = World->SpawnActorDeferred<ABMTile>(
				TileClass, FTransform(FRotator::ZeroRotator, SpawnedTileLocation));

			Tile->SetTileArrayCoordinates(i, j);

			// Make tiles at border have Unbreakable walls
			if (i == 0 || j == 0 || i + 1 == GameInstance->GetMapSizeX() || j + 1 == GameInstance->GetMapSizeY())
				Tile->SetWallType(EWallType::Unbreakable);


			// Make tiles empty near player spawn  
			if ((i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 1))
				Tile->SetWallType(EWallType::None);

			// Make tiles empty at the npcs spawn
			if (i == GameInstance->GetMapSizeX() - 2 && j != 0 && j != GameInstance->GetMapSizeY() - 1)
			{
				Tile->SetWallType(EWallType::None);
				
				// Set Tiles to green color, so player can see finish border
				UMaterialInstanceDynamic* Material = Tile->GetTileMesh()->CreateAndSetMaterialInstanceDynamic(0);
				if(Material) Material->SetVectorParameterValue("BaseColor", FLinearColor::Green);
			}

			// Make tiles Unbreakable at the middle of the map with a ~chess pattern 
			if (i % 2 == 0 && j % 2 == 0 &&
				i < GameInstance->GetMapSizeX() - 2 && j < GameInstance->GetMapSizeY() - 2)
				Tile->SetWallType(EWallType::Unbreakable);

			if (Threshold != 0.0) Threshold -= 0.001;

			Tile->SetThreshold(Threshold);
			Tile->FinishSpawning(FTransform(FRotator::ZeroRotator, SpawnedTileLocation));
			TileList.Add(Tile);

			SpawnedTileLocation.X += StepShift;
		}

		SpawnedTileLocation.X = 0;
		SpawnedTileLocation.Y += StepShift;
	}
}

void ABMGameModeBase::SpawnPlayer()
{
	FVector SpawnLocation = FVector::ZeroVector;

	for (auto* Tile : TileList)
	{
		if (Tile->GetTileArrayCoordinates().CoordinateX == 1 && Tile->GetTileArrayCoordinates().CoordinateY == 1)
		{
			SpawnLocation = Tile->GetActorLocation();
			SpawnLocation.Z += 100;
			break;
		}
	}

	// TODO Spawn PlayerSpawner instead, so player can respawn if i implement such feature.
	ABMPlayerCharacter* Player = GetWorld()->SpawnActor<ABMPlayerCharacter>(PlayerClass, SpawnLocation,
	                                                                        FRotator::ZeroRotator);
	if (!Player) return;

	ABMPlayerController* PlayerController = Cast<
		ABMPlayerController>(GetWorld()->GetFirstPlayerController());

	if (!PlayerController) return;
	PlayerController->Possess(Player);
}

void ABMGameModeBase::SpawnEnemy()
{
	for (auto* Tile : TileList)
	{
		if (EnemySpawnAmount <= 0) return;

		FTileArrayCoordinates TileCoordinates = Tile->GetTileArrayCoordinates();

		if (TileCoordinates.CoordinateX == GameInstance->GetMapSizeX() - 2 &&
			TileCoordinates.CoordinateY != 0 &&
			TileCoordinates.CoordinateY != GameInstance->GetMapSizeY() - 1)
		{
			ABMAICharacter* Enemy = GetWorld()->SpawnActor<ABMAICharacter>(EnemyClass, Tile->GetActorLocation(),
			                                                               FRotator::ZeroRotator);

			if (!Enemy) continue;
			--EnemySpawnAmount;
		}
	}
}

void ABMGameModeBase::SpawnTriggerFinish()
{
	// Trigger Finish will spawn at the center of Y tile array
	int32 MeanYCoordinate = GameInstance->GetMapSizeY() / 2;

	for (auto* Tile : TileList)
	{
		if (GameInstance->GetMapSizeX() - 2 == Tile->GetTileArrayCoordinates().CoordinateX &&
			Tile->GetTileArrayCoordinates().CoordinateY == MeanYCoordinate)
		{
			TriggerFinish = GetWorld()->SpawnActor<ATriggerBox>(TriggerFinishClass, Tile->GetActorLocation(),
			                                                    FRotator::ZeroRotator);
			break;
		}
	}
	if (!TriggerFinish) return;

	// This scale will mostly cover all area where player can be in order to finish level.
	const int32 TriggerScaleX = GameInstance->GetMapSizeY() * 3;
	TriggerFinish->SetActorScale3D(FVector(TriggerScaleX, 2, 4));
}
