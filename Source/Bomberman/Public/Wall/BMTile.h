// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BMTile.generated.h"

UENUM(BlueprintType)
enum class EWallType : uint8
{
	None = 0,
	Random = 1,
	Breakable = 2,
	Unbreakable = 3
};

USTRUCT(BlueprintType)
struct FTileArrayCoordinates
{
	GENERATED_USTRUCT_BODY()

	int32 CoordinateX = 0;
	int32 CoordinateY = 0;
};

UCLASS()
class BOMBERMAN_API ABMTile : public AActor
{
	GENERATED_BODY()

public:
	ABMTile();


	// Prevent player to place bomb on a tile that already has a bomb.
	bool HasBomb = false;

	void SetWallType(const EWallType NewWallType) { WallType = NewWallType; }
	EWallType GetWallType() const { return WallType; }

	void DestroyWall();

	void SetThreshold(float NewThreshold);
	FTileArrayCoordinates GetTileArrayCoordinates() const { return ArrayCoordinates; }

	void SetTileArrayCoordinates(int32 const X, int32 const Y)
	{
		ArrayCoordinates.CoordinateX = X;
		ArrayCoordinates.CoordinateY = Y;
	}

	UStaticMeshComponent* GetTileMesh() const { return TileMesh; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	EWallType WallType = EWallType::None;

	/** Used to determine a limit when a random wall should be generated or not.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Threshold = 0.9;

	UPROPERTY()
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* TileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* BreakableWallMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Mesh")
	UStaticMeshComponent* UnbreakableWallMesh;


	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	FTileArrayCoordinates ArrayCoordinates;

	void GenerateWall();
};
