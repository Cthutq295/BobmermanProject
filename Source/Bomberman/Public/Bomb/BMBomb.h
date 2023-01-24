// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "BMDamageZone.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Wall/BMTile.h"
#include "BMBomb.generated.h"

UCLASS()
class BOMBERMAN_API ABMBomb : public AActor
{
	GENERATED_BODY()

public:
	ABMBomb();

	void SetOccupiedTile(ABMTile* Tile);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* BombMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ExplodeTime = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int ExplodeRadiusXDirection = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int ExplodeRadiusYDirection = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<ABMDamageZone> DamageZoneClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	URadialForceComponent* RadialForceComponent;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	bool DuFullDamage = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 50.f;

	virtual void BeginPlay() override;

private:
	// A tile that has bomb on it.
	UPROPERTY()
	ABMTile* OccupiedTile = nullptr;

	UPROPERTY()
	TArray<ABMTile*> TilesToBomb;

	FTimerHandle BombExplodeTimerHandle;

	void FindNeighborTiles();

	void Explode();
};
