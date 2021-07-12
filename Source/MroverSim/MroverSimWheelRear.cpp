// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimWheelRear.h"

UMroverSimWheelRear::UMroverSimWheelRear()
{
	ShapeRadius = 35.f;
	ShapeWidth = 35.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 0.f;
	LatStiffValue = 5;
}
