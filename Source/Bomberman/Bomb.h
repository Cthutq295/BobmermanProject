#pragma once

#include "CoreMinimal.h"
#include "KillZone.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	

	ABomb();

	UPROPERTY(EditAnywhere)
	USceneComponent *SceneComponent;
	
	FTimerHandle TimerHandler;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BombMesh;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin="1", ClampMax = "3"))
	int ExplodeTime = 2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AKillZone> KillBox;

	UPROPERTY(EditAnywhere)
	class UParticleSystem *ExplodeParticle;

	UPROPERTY(EditAnywhere)

	class USoundBase* ExplodeSound;

private:
	TArray<ATile*> DetectedTiles;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckTilesToBomb();
	
	UFUNCTION()
	void DoExplosion();
	
};
