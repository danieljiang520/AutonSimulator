// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimGameMode.h"
#include "MroverSimPawn.h"
#include "MroverSimHud.h"

AMroverSimGameMode::AMroverSimGameMode()
{
	DefaultPawnClass = AMroverSimPawn::StaticClass();
	HUDClass = AMroverSimHud::StaticClass();
}
