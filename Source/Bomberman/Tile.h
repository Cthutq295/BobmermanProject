
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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


public:	

	//virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void GenerateWalls();

};
