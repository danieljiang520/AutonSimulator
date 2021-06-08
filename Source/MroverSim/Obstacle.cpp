// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle(){}


// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

 	FActorSpawnParameters SpawnParams;

	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation, SpawnParams);
	
}
