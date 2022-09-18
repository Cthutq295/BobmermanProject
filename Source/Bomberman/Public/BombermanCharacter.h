// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "GameFramework/Character.h"
#include "BombermanCharacter.generated.h"

UCLASS(config=Game)
class ABombermanCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
public:
	ABombermanCharacter();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABomb> Bomb;
	
	UPROPERTY(EditAnywhere, meta = ( ClampMin="1", ClampMax="3"))
	int BombPlaceCoolDown = 2;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void OnPlaceBomb();
	
	void OnLeaveGame();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	
	UPROPERTY()
	class UAIPerceptionStimuliSourceComponent* stimulus;
	
	bool IsReadyToPlaceBomb = true;
    	
	FTimerHandle Timer;

	void setup_stimulus();

	void ResetCoolDown();
};

