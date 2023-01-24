// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Components/BMHealthComponent.h"
#include "GameFramework/Character.h"
#include "BMBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UENUM()
enum class ECharacterType : uint8
{
	NPC = 0,
	Player = 1
};

UCLASS()
class BOMBERMAN_API ABMBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABMBaseCharacter();

	ECharacterType GetCharacterType() const { return CharacterType; }
	void SetCharacterType(ECharacterType NewType) { CharacterType = NewType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ragdoll", meta=(ClampMin = 1))
	int RagdollTimeExistence = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UBMHealthComponent* HealthComponent;

	ECharacterType CharacterType;

	virtual void BeginPlay() override;

	virtual void OnDeath();

public:
	virtual void Tick(float DeltaTime) override;
};
