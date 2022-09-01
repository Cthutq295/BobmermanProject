
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class BOMBERMAN_API ATile : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	USceneComponent *SceneComponent;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *TileMesh;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *WallMesh = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BlockMesh;

	UPROPERTY(EditAnywhere)
	bool HasWall = true;

	UPROPERTY(EditAnywhere)
	bool IsBlocked = false;
	
	ATile();

protected:
	
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;


public:	

	UFUNCTION()
	void GenerateWalls();

};
