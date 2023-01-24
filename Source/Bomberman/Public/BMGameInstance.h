// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Bomberman/BMUtils.h"
#include "Engine/GameInstance.h"
#include "BMGameInstance.generated.h"

UCLASS()
class BOMBERMAN_API UBMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetMapSizeX(int32 const NewMapSize);
	void SetMapSizeY(int32 const NewMapSize);

	int32 GetMapSizeX() const { return MapSizeX; }
	int32 GetMapSizeY() const { return MapSizeY; }

private:
	int32 MapSizeX = BMUtils::MinMapSize;
	int32 MapSizeY = BMUtils::MinMapSize;
};
