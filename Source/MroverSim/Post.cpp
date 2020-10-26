// Fill out your copyright notice in the Description page of Project Settings.


#include "Post.h"


// Sets default values
APost::APost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

