// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "MroverSimHud.generated.h"


UCLASS(config = Game)
class AMroverSimHud : public AHUD
{
	GENERATED_BODY()

public:
	AMroverSimHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
