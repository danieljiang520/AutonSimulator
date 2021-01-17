// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LCM_Handler.h"

THIRD_PARTY_INCLUDES_START
#include <lcm/lcm-cpp.hpp>
#include <lcm/rover_msgs/GPS.hpp>
THIRD_PARTY_INCLUDES_END

// Must always be last include
#include "Post.generated.h"

UCLASS()
class MROVERSIM_API APost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	lcm::LCM lcm;
	LCM_Handler handlerObject;
};
