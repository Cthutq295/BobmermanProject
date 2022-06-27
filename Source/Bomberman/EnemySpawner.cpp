// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"



void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(timer, this, &AEnemySpawner::SpawnEnemy, 6, true);
}

void AEnemySpawner::SpawnEnemy()
{
	FRotator rotation = GetActorRotation();
	FVector location = GetActorLocation();
	FActorSpawnParameters params;
	AAIEnemy *SpawnEnemy = GetWorld()->SpawnActor<AAIEnemy>(Enemy, location, rotation, params);
	
}
