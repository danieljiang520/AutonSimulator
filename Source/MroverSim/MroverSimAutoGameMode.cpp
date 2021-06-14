// Fill out your copyright notice in the Description page of Project Settings.


#include "MroverSimAutoGameMode.h"
#include "MroverSimPawnAuto.h"
#include "MroverSimHud.h"

AMroverSimAutoGameMode::AMroverSimAutoGameMode()
{
	DefaultPawnClass = AMroverSimPawnAuto::StaticClass();
	HUDClass = AMroverSimHud::StaticClass();
}