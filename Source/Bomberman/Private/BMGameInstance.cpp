// Bomberman Test Project. 


#include "BMGameInstance.h"

#include "Bomberman/BMUtils.h"

void UBMGameInstance::SetMapSizeX(int32 const NewMapSize)
{
	MapSizeX = FMath::Clamp(NewMapSize, BMUtils::MinMapSize, BMUtils::MaxMapSize);
}

void UBMGameInstance::SetMapSizeY(int32 const NewMapSize)
{
	MapSizeY = FMath::Clamp(NewMapSize, BMUtils::MinMapSize, BMUtils::MaxMapSize);
}
