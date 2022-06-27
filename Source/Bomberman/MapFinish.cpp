// Fill out your copyright notice in the Description page of Project Settings.


#include "MapFinish.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMapFinish::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMapFinish::OnPlayerBeginOverlap);
	GameMode = Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AMapFinish::OnPlayerBeginOverlap(AActor* actor, AActor* otherActor)
{
	
	if (otherActor && otherActor != this && otherActor->GetClass()->GetName() == "ThirdPersonCharacter_C" )
	{
		/*
		if(IsValid(LevelWinClass))
		{
			UUserWidget *Widget = CreateWidget(GetWorld(), LevelWinClass);
			Controller->SetShowMouseCursor(true);
			Widget->AddToViewport();
			
		} */
		otherActor->Destroy();
		GameMode->ShowWinWidget();
		
	}
}
