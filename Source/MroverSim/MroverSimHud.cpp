// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimHud.h"
#include "MroverSimPawn.h"
#include "WheeledVehicle.h"
#include "RenderResource.h"
#include "Shader.h"
#include "Engine/Canvas.h"
#include "WheeledVehicleMovementComponent.h"
#include "Engine/Font.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "VehicleHUD"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

AMroverSimHud::AMroverSimHud()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
}

void AMroverSimHud::DrawHUD()
{
	Super::DrawHUD();

	// Calculate ratio from 720p
	const float HUDXRatio = Canvas->SizeX / 1280.f;
	const float HUDYRatio = Canvas->SizeY / 720.f;

	bool bWantHUD = true;
#if HMD_MODULE_INCLUDED
	bWantHUD = !GEngine->IsStereoscopic3D();
#endif // HMD_MODULE_INCLUDED
	// We dont want the onscreen hud when using a HMD device	
	if (bWantHUD == true)
	{
		// Get our vehicle so we can check if we are in car. If we are we don't want onscreen HUD
		AMroverSimPawn* Vehicle = Cast<AMroverSimPawn>(GetOwningPawn());
		if ((Vehicle != nullptr) && (Vehicle->bInCarCameraActive == false))
		{
			FVector2D ScaleVec(HUDYRatio * 0.8f, HUDYRatio * 0.8f);

			// Speed
			FCanvasTextItem SpeedTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 390), Vehicle->SpeedDisplayString, HUDFont, FLinearColor::White);
			SpeedTextItem.Scale = ScaleVec;
			Canvas->DrawItem(SpeedTextItem);

			// NavState
			FCanvasTextItem NavStateTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 430.f), Vehicle->NavStateStatusDisplayString, HUDFont, FLinearColor::White);
			NavStateTextItem.Scale = ScaleVec;
			Canvas->DrawItem(NavStateTextItem);

			// Waypoints
			FCanvasTextItem WaypointTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 470.f), Vehicle->WaypointsDisplayString, HUDFont, FLinearColor::White);
			WaypointTextItem.Scale = ScaleVec;
			Canvas->DrawItem(WaypointTextItem);

			// JoystickTranslational
			FCanvasTextItem JoystickTranslationalTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 470.f), Vehicle->JoystickTranslationalDisplayString, HUDFont, FLinearColor::White);
			JoystickTranslationalTextItem.Scale = ScaleVec;
			Canvas->DrawItem(JoystickTranslationalTextItem);

			// JoystickRotational
			FCanvasTextItem JoystickRotationalTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 490.f), Vehicle->JoystickRotationalDisplayString, HUDFont, FLinearColor::White);
			JoystickRotationalTextItem.Scale = ScaleVec;
			Canvas->DrawItem(JoystickRotationalTextItem);

			// OdometryLatitude
			FCanvasTextItem OdometryLatitudeTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 530.f), Vehicle->OdometryLatitudeDisplayString, HUDFont, FLinearColor::White);
			OdometryLatitudeTextItem.Scale = ScaleVec;
			Canvas->DrawItem(OdometryLatitudeTextItem);

			// OdometryLongitude
			FCanvasTextItem OdometryLongitudeTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 550.f), Vehicle->OdometryLongitudeDisplayString, HUDFont, FLinearColor::White);
			OdometryLongitudeTextItem.Scale = ScaleVec;
			Canvas->DrawItem(OdometryLongitudeTextItem);

			// OdometryHeading
			FCanvasTextItem OdometryHeadingTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 570.f), Vehicle->OdometryHeadingDisplayString, HUDFont, FLinearColor::White);
			OdometryHeadingTextItem.Scale = ScaleVec;
			Canvas->DrawItem(OdometryHeadingTextItem);

			// ObstacleDistance
			FCanvasTextItem ObstacleDistanceTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 550.f), Vehicle->ObstacleDistanceDisplayString, HUDFont, FLinearColor::White);
			ObstacleDistanceTextItem.Scale = ScaleVec;
			Canvas->DrawItem(ObstacleDistanceTextItem);

			// ObstacleBearing
			FCanvasTextItem ObstacleBearingTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 570.f), Vehicle->ObstacleBearingDisplayString, HUDFont, FLinearColor::White);
			ObstacleBearingTextItem.Scale = ScaleVec;
			Canvas->DrawItem(ObstacleBearingTextItem);

			// RadioStrength
			FCanvasTextItem RadioStrengthTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 510.f), Vehicle->RadioStrengthDisplayString, HUDFont, FLinearColor::White);
			RadioStrengthTextItem.Scale = ScaleVec;
			Canvas->DrawItem(RadioStrengthTextItem);

			// TargetOneDistance
			FCanvasTextItem TargetOneDistanceTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 610.f), Vehicle->TargetOneDistanceDisplayString, HUDFont, FLinearColor::White);
			TargetOneDistanceTextItem.Scale = ScaleVec;
			Canvas->DrawItem(TargetOneDistanceTextItem);

			// TargetOneBearing
			FCanvasTextItem TargetOneBearingTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 630.f), Vehicle->TargetOneBearingDisplayString, HUDFont, FLinearColor::White);
			TargetOneBearingTextItem.Scale = ScaleVec;
			Canvas->DrawItem(TargetOneBearingTextItem);

			// TargetOneID
			FCanvasTextItem TargetOneIDTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 650.f), Vehicle->TargetOneIDDisplayString, HUDFont, FLinearColor::White);
			TargetOneIDTextItem.Scale = ScaleVec;
			Canvas->DrawItem(TargetOneIDTextItem);

			// TargetTwoDistance
			FCanvasTextItem TargetTwoDistanceTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 610.f), Vehicle->TargetTwoDistanceDisplayString, HUDFont, FLinearColor::White);
			TargetTwoDistanceTextItem.Scale = ScaleVec;
			Canvas->DrawItem(TargetTwoDistanceTextItem);

			// TargetTwoBearing
			FCanvasTextItem TargetTwoBearingTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 630.f), Vehicle->TargetTwoBearingDisplayString, HUDFont, FLinearColor::White);
			TargetTwoBearingTextItem.Scale = ScaleVec;
			Canvas->DrawItem(TargetTwoBearingTextItem);

			// TargetTwoID
			FCanvasTextItem TargetTwoIDTextItem(FVector2D(HUDXRatio * 1100.f, HUDYRatio * 650.f), Vehicle->TargetTwoIDDisplayString, HUDFont, FLinearColor::White);
			TargetTwoIDTextItem.Scale = ScaleVec;
			Canvas->DrawItem(TargetTwoIDTextItem);


		}
	}
}


#undef LOCTEXT_NAMESPACE
