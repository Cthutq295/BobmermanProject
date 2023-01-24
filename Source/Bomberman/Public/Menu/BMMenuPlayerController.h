// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BMMenuPlayerController.generated.h"

UCLASS()
class BOMBERMAN_API ABMMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
