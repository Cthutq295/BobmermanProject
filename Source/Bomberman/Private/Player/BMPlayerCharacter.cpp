// Bomberman Test Project. 

#include "Player/BMPlayerCharacter.h"

#include "BMGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BMPlayerState.h"

ABMPlayerCharacter::ABMPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

float ABMPlayerCharacter::GetBombCooldownPercent() const
{
	return GetWorldTimerManager().IsTimerActive(BombResetTimerHandle)
		       ? GetWorldTimerManager().GetTimerElapsed(BombResetTimerHandle) / BombPlaceCooldown
		       : 1.0;
}

void ABMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterType = ECharacterType::Player;

	if (CameraResetAngleCurveFloat && AllowAutoCameraReset)
	{
		FOnTimelineFloat ResetAngleProgress;
		ResetAngleProgress.BindUFunction(this, FName("ResetCameraAngleUpdate"));
		CameraResetAngleTimeline.AddInterpFloat(CameraResetAngleCurveFloat, ResetAngleProgress);
		CameraResetAngleTimeline.SetLooping(false);
	}
	HealthComponent->OnDeath.AddUObject(this, &ABMPlayerCharacter::OnDeath);

	SetCameraRotationLimits();
}

void ABMPlayerCharacter::SetCameraRotationLimits() const
{
	if (!GetWorld()) return;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMin = CameraMinOffset;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMax = CameraMaxOffset;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewRollMin = CameraMinOffset;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewRollMax = CameraMaxOffset;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewYawMin = CameraMinOffset;
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewYawMax = CameraMaxOffset;
}

void ABMPlayerCharacter::StartCameraReset()
{
	if (CameraResetAngleTimeline.IsPlaying()) return;

	CameraResetAngleTimeline.PlayFromStart();
}

void ABMPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	ABMPlayerState* State = Controller->GetPlayerState<ABMPlayerState>();
	if(State) State->ShowDeathWidget(Cast<ABMPlayerController>(GetController()));
}

void ABMPlayerCharacter::ResetCameraAngleUpdate(float Alpha) const
{
	Controller->SetControlRotation(FMath::Lerp(Controller->GetControlRotation(), DefaultCameraRotation, Alpha));
}

void ABMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraResetAngleTimeline.TickTimeline(DeltaTime);
}

void ABMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABMPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABMPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABMPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ABMPlayerCharacter::TurnAround);
	PlayerInputComponent->BindAction("PlaceBomb", IE_Pressed, this, &ABMPlayerCharacter::PlaceBomb);
}

void ABMPlayerCharacter::MoveForward(float Amount)
{
	// find out which way is forward
	const FRotator YawRotation(0, 0, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Amount);
}

void ABMPlayerCharacter::MoveRight(float Amount)
{
	// find out which way is right
	const FRotator YawRotation(0, 0, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Amount);
}

void ABMPlayerCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);

	// Stop camera angle reset. Start count down for the next reset.
	if (FMath::Abs(Amount) > 0.01)
	{
		CameraResetAngleTimeline.Stop();
		GetWorldTimerManager().ClearTimer(CameraResetTimerHandle);
		GetWorldTimerManager().SetTimer(CameraResetTimerHandle, this, &ABMPlayerCharacter::StartCameraReset,
		                                CameraResetRate, false);
	}
}

void ABMPlayerCharacter::TurnAround(float Amount)
{
	AddControllerRollInput(Amount);

	// Stop camera angle reset. Start count down for the next reset.
	if (FMath::Abs(Amount) > 0.01)
	{
		CameraResetAngleTimeline.Stop();
		GetWorldTimerManager().ClearTimer(CameraResetTimerHandle);
		GetWorldTimerManager().SetTimer(CameraResetTimerHandle, this, &ABMPlayerCharacter::StartCameraReset,
		                                CameraResetRate, false);
	}
}

void ABMPlayerCharacter::PlaceBomb()
{
	const auto World = GetWorld();
	if (!World || !IsReadyToPlaceBomb || !BombClass) return;

	if (HealthComponent->IsDead()) return;

	float TraceDistance = 300.f;

	const FVector TraceStart = GetCapsuleComponent()->GetComponentLocation();
	const FVector TraceDirection = -GetCapsuleComponent()->GetUpVector();
	const FVector TraceEnd = TraceStart + TraceDirection * TraceDistance;

	FHitResult HitResult;
	World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

	if (!HitResult.bBlockingHit) return;

	const auto Tile = Cast<ABMTile>(HitResult.Actor);
	if (!Tile || Tile->HasBomb) return;

	float const SpawnOffsetZ = 100.f;
	FVector SpawnLocation = HitResult.Actor->GetActorLocation();
	SpawnLocation.Z += SpawnOffsetZ;

	ABMBomb* Bomb = World->SpawnActor<ABMBomb>(BombClass, SpawnLocation, FRotator::ZeroRotator);
	Bomb->SetOccupiedTile(Tile);

	IsReadyToPlaceBomb = false;
	Tile->HasBomb = true;

	GetWorldTimerManager().SetTimer(BombResetTimerHandle, this, &ABMPlayerCharacter::SetBombCooldown,
	                                BombPlaceCooldown, false);
}

void ABMPlayerCharacter::SetBombCooldown()
{
	IsReadyToPlaceBomb = true;
}
