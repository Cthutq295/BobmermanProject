// Bomberman Test Project. 

#pragma once

#include "CoreMinimal.h"
#include "Bomb/BMBomb.h"
#include "Components/TimelineComponent.h"
#include "Player/BMBaseCharacter.h"
#include "BMPlayerCharacter.generated.h"

UCLASS()
class BOMBERMAN_API ABMPlayerCharacter : public ABMBaseCharacter
{
	GENERATED_BODY()
public:
	ABMPlayerCharacter();

	float GetBombCooldownPercent() const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	UCurveFloat* CameraResetAngleCurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta=(ClampMin = -90, ClampMax = 90))
	float CameraMinOffset = -8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta=(ClampMin = -90, ClampMax = 90))
	float CameraMaxOffset = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool AllowAutoCameraReset = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraResetRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bomb")
	TSubclassOf<ABMBomb> BombClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bomb")
	float BombPlaceCooldown = 3.0f;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

private:
	FTimeline CameraResetAngleTimeline;

	FRotator const DefaultCameraRotation = FRotator(0, 0, 0);

	FTimerHandle CameraResetTimerHandle;

	bool IsReadyToPlaceBomb = true;
	FTimerHandle BombResetTimerHandle;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookUp(float Amount);
	void TurnAround(float Amount);

	void PlaceBomb();
	void SetBombCooldown();

	void SetCameraRotationLimits() const;

	void StartCameraReset();

	UFUNCTION()
	void ResetCameraAngleUpdate(float Alpha) const;
};
