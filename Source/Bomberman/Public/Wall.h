
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class BOMBERMAN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere)
	bool IsDestructible = true;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *WallMesh;
	AWall();

protected:
	
	virtual void BeginPlay() override;

};
