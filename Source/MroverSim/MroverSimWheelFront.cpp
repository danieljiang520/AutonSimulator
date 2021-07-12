// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimWheelFront.h"

UMroverSimWheelFront::UMroverSimWheelFront()
{
	ShapeRadius = 35.f;
	ShapeWidth = 35.0f;
	bAffectedByHandbrake = false;
	SteerAngle = 50.f;
	LatStiffValue = 5;
}
