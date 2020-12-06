// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimPawn.h"
#include "MroverSimWheelFront.h"
#include "MroverSimWheelRear.h"
#include "MroverSimHud.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextRenderComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Controller.h"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

// Needed for VR Headset
#if HMD_MODULE_INCLUDED
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#endif // HMD_MODULE_INCLUDED

const FName AMroverSimPawn::LookUpBinding("LookUp");
const FName AMroverSimPawn::LookRightBinding("LookRight");

#define LOCTEXT_NAMESPACE "VehiclePawn"

AMroverSimPawn::AMroverSimPawn(const class FObjectInitializer& PCIP) :
 Super(PCIP.SetDefaultSubobjectClass<USimpleWheeledVehicleMovementComponent>(AWheeledVehicle::VehicleMovementComponentName))
{
	// Car mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/Vehicle/Rover/Complete_Rover.Complete_Rover"));
	GetMesh()->SetSkeletalMesh(CarMesh.Object);

	static ConstructorHelpers::FClassFinder<UObject> AnimBPClass(TEXT("/Game/Vehicle/Rover/Complete_Rover_Skeleton_AnimBlueprint"));
	GetMesh()->SetAnimInstanceClass(AnimBPClass.Class);

	// Simulation
	VehicleSimple = CastChecked<USimpleWheeledVehicleMovementComponent>(GetVehicleMovement());

	VehicleSimple->WheelSetups.SetNum(4);

	VehicleSimple->WheelSetups[0].WheelClass = UMroverSimWheelFront::StaticClass();
	VehicleSimple->WheelSetups[0].BoneName = FName("Wheel_Front_Left");
	VehicleSimple->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	VehicleSimple->WheelSetups[1].WheelClass = UMroverSimWheelFront::StaticClass();
	VehicleSimple->WheelSetups[1].BoneName = FName("Wheel_Front_Right");
	VehicleSimple->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	VehicleSimple->WheelSetups[2].WheelClass = UMroverSimWheelRear::StaticClass();
	VehicleSimple->WheelSetups[2].BoneName = FName("Wheel_Rear_Left");
	VehicleSimple->WheelSetups[2].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	VehicleSimple->WheelSetups[3].WheelClass = UMroverSimWheelRear::StaticClass();
	VehicleSimple->WheelSetups[3].BoneName = FName("Wheel_Rear_Right");
	VehicleSimple->WheelSetups[3].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;
}
	void AMroverSimPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AMroverSimPawn::MoveForward);
	PlayerInputComponent->BindAction("MoveForward", IE_Released, this, &AMroverSimPawn::ResetWheelTorque);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &AMroverSimPawn::MoveBackward);
	PlayerInputComponent->BindAction("MoveBackward", IE_Released, this, &AMroverSimPawn::ResetWheelTorque);
	PlayerInputComponent->BindAction("TurnRight", IE_Pressed, this, &AMroverSimPawn::TurnRight);
	PlayerInputComponent->BindAction("TurnRight", IE_Released, this, &AMroverSimPawn::ResetWheelTorque);
	PlayerInputComponent->BindAction("TurnLeft", IE_Pressed, this, &AMroverSimPawn::TurnLeft);
	PlayerInputComponent->BindAction("TurnLeft", IE_Released, this, &AMroverSimPawn::ResetWheelTorque);
}

void AMroverSimPawn::MoveForward()
{
	VehicleSimple->SetDriveTorque(1000,FRONT_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(1000,FRONT_RIGHT_WHEEL);
	VehicleSimple->SetDriveTorque(1000,BACK_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(1000,BACK_RIGHT_WHEEL);
}

void AMroverSimPawn::MoveBackward()
{
	VehicleSimple->SetDriveTorque(-1000,FRONT_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(-1000,FRONT_RIGHT_WHEEL);
	VehicleSimple->SetDriveTorque(-1000,BACK_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(-1000,BACK_RIGHT_WHEEL);
}

void AMroverSimPawn::TurnRight()
{
	VehicleSimple->SetDriveTorque(1000,FRONT_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(-1000,FRONT_RIGHT_WHEEL);
	VehicleSimple->SetDriveTorque(1000,BACK_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(-1000,BACK_RIGHT_WHEEL);
}

void AMroverSimPawn::TurnLeft()
{
	VehicleSimple->SetDriveTorque(-1000,FRONT_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(1000,FRONT_RIGHT_WHEEL);
	VehicleSimple->SetDriveTorque(-1000,BACK_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(1000,BACK_RIGHT_WHEEL);
}

void AMroverSimPawn::ResetWheelTorque()
{
	VehicleSimple->SetDriveTorque(0,FRONT_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(0,FRONT_RIGHT_WHEEL);
	VehicleSimple->SetDriveTorque(0,BACK_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(0,BACK_RIGHT_WHEEL);
}

void AMroverSimPawn::Tick(float Delta)
{
	Super::Tick(Delta);
	
	// Update the strings used in the hud (incar and onscreen)
	UpdateHUDStrings();

	// Update Rover Position
	UpdateRoverPosition();

	bool bHMDActive = false;
#if HMD_MODULE_INCLUDED
	if ((GEngine->XRSystem.IsValid() == true) && ((GEngine->XRSystem->IsHeadTrackingAllowed() == true) || (GEngine->IsStereoscopic3D() == true)))
	{
		bHMDActive = true;
	}
#endif // HMD_MODULE_INCLUDED
	if (bHMDActive == false)
	{
		if ( (InputComponent) && (bInCarCameraActive == true ))
		{
			FRotator HeadRotation = InternalCamera->GetRelativeRotation();
			HeadRotation.Pitch += InputComponent->GetAxisValue(LookUpBinding);
			HeadRotation.Yaw += InputComponent->GetAxisValue(LookRightBinding);
			InternalCamera->SetRelativeRotation(HeadRotation);
		}
	}
}

void AMroverSimPawn::BeginPlay()
{
	Super::BeginPlay();
}

AMroverSimPawn::Coordinate AMroverSimPawn::ConvertCoordinate(const float &position, const std::string &choice){
	AMroverSimPawn::Coordinate temp;

	double temp_minutes = static_cast<double>(position) * CM_MINUTE_SF;

	if(choice == "latitude")
		temp_minutes = URC_LATITUDE_MINUTE + temp_minutes;
	else
		temp_minutes = URC_LONGITUDE_MINUTE + temp_minutes;
	
	temp.degree = trunc(temp_minutes / 60);

	temp.minute = (temp_minutes - temp.degree*60);

	return temp;
}

double AMroverSimPawn::ConvertYaw(const float &yaw){
	if(yaw < 0){
		return 360 + static_cast<double>(yaw);
	} else {
		return yaw;
	}
}

void AMroverSimPawn::UpdateRoverPosition(){
	/*
	FVector rover_location = GetActorLocation();
	FRotator rover_rotation = GetActorRotation();
	
	
	float rover_latitude = URC_LATITUDE - rover_location.Y * CM_DEGREE_SF;
	float rover_longitude = URC_LONGITUDE + rover_location.X * CM_DEGREE_SF;
	float rover_heading = rover_rotation.Yaw;
	*/

	rover_position.latitude = AMroverSimPawn::ConvertCoordinate(GetActorLocation().X,"latitude");
	rover_position.longitude = AMroverSimPawn::ConvertCoordinate(GetActorLocation().Y,"longitude");
	rover_position.heading = AMroverSimPawn::ConvertYaw(GetActorRotation().Yaw);
}

void AMroverSimPawn::UpdateHUDStrings()
{
	float KPH = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);

	double RoundedLatitudeMinutes = (double)((int)(rover_position.latitude.minute*100))/100;
	double RoundedLongitudeMinutes = (double)((int)(rover_position.longitude.minute*100))/100;
	double RoundedHeading = (double)((int)(rover_position.heading*100))/100;

	std::string ConvertedLatitudeMinutes = std::to_string(RoundedLatitudeMinutes);
	std::string ConvertedLongitudeMinutes = std::to_string(RoundedLongitudeMinutes);
	std::string ConvertedHeading = std::to_string(RoundedHeading);

	for(int i = 0; i < 4; ++i){
		ConvertedLatitudeMinutes.pop_back();
		ConvertedLongitudeMinutes.pop_back();
		ConvertedHeading.pop_back();
	}

	std::string LatitudeOdeometryLine = std::to_string(rover_position.latitude.degree) + DEGREE_SYMBOL + 
			ConvertedLatitudeMinutes + MINUTE_SYMBOL;

	std::string LongitudeOdeometryLine = std::to_string(rover_position.longitude.degree) + DEGREE_SYMBOL + 
			ConvertedLongitudeMinutes + MINUTE_SYMBOL;

	std::string HeadingOdeometryLine = ConvertedHeading + DEGREE_SYMBOL;

	/*
	FText LatitudeOdeometryLine[4] = {FText::AsNumber(rover_position.latitude.degree), FText::FromString(DEGREE_SYMBOL), 
			FText::AsNumber(rover_position.latitude.minute), FText::FromString(MINUTE_SYMBOL)};
	
	FText LongitudeOdeometryLine[4] = {FText::AsNumber(rover_position.longitude.degree), FText::FromString(DEGREE_SYMBOL), 
			FText::AsNumber(rover_position.longitude.minute), FText::FromString(MINUTE_SYMBOL)};

	FText latitude = FText::Join(LatitudeOdeometryLine);
	FText longitude = FText::Join(LongitudeOdeometryLine);

	
	FText latitude = FText::AsNumber(rover_position.latitude.degree) + FText(DEGREE_SYMBOL) + 
			FText::AsNumber(rover_position.latitude.minute) + FText(MINUTE_SYMBOL;
	
	FText longitude = FText::AsNumber(rover_position.longitude.degree) + FText(DEGREE_SYMBOL) + 
			FText::AsNumber(rover_position.longitude.minute) + FText(MINUTE_SYMBOL);
	*/
	// Using FText because this is display text that should be localizable
	SpeedDisplayString = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH_int));

	NavStateStatusDisplayString = FText::Format(LOCTEXT("NavStateFormat", "Navigation State: {0}"), FText::AsNumber(0));

	WaypointsDisplayString = FText::Format(LOCTEXT("WaypointsFormat", "Waypoints: {0}"), FText::AsNumber(0));

	JoystickTranslationalDisplayString = FText::Format(LOCTEXT("JoystickTranslationalFormat", "JoystickTranslational: {0}"), FText::AsNumber(0));

	JoystickRotationalDisplayString = FText::Format(LOCTEXT("JoystickRotationalFormat", "JoystickRotational: {0}"), FText::AsNumber(0));

	OdometryLatitudeDisplayString = FText::Format(LOCTEXT("OdometryLatitudeFormat", "OdometryLatitude: {0}"), FText::FromString(LatitudeOdeometryLine.c_str()));

	OdometryLongitudeDisplayString = FText::Format(LOCTEXT("OdometryLongitudeFormat", "OdometryLongitude: {0}"), FText::FromString(LongitudeOdeometryLine.c_str()));

	OdometryHeadingDisplayString = FText::Format(LOCTEXT("OdometryHeadingFormat", "OdometryHeading: {0}"), FText::FromString(HeadingOdeometryLine.c_str()));

	ObstacleDistanceDisplayString = FText::Format(LOCTEXT("ObstacleDistanceFormat", "ObstacleDistance: {0}"), FText::AsNumber(0));

	ObstacleBearingDisplayString = FText::Format(LOCTEXT("ObstacleBearingFormat", "ObstacleBearing: {0}"), FText::AsNumber(0));

	RadioStrengthDisplayString = FText::Format(LOCTEXT("RadioStrengthFormat", "RadioStrength: {0}"), FText::AsNumber(0));

	TargetOneDistanceDisplayString = FText::Format(LOCTEXT("TargetOneDistanceFormat", "TargetOneDistance: {0}"), FText::AsNumber(0));

	TargetOneBearingDisplayString = FText::Format(LOCTEXT("TargetOneBearingFormat", "TargetOneBearing: {0}"), FText::AsNumber(0));

	TargetOneIDDisplayString = FText::Format(LOCTEXT("TargetOneIDFormat", "TargetOneID: {0}"), FText::AsNumber(0));

	TargetTwoDistanceDisplayString = FText::Format(LOCTEXT("TargetTwoDistanceFormat", "TargetTwoDistance: {0}"), FText::AsNumber(0));

	TargetTwoBearingDisplayString = FText::Format(LOCTEXT("TargetTwoBearingFormat", "TargetTwoBearing: {0}"), FText::AsNumber(0));

	TargetTwoIDDisplayString = FText::Format(LOCTEXT("TargetTwoIDFormat", "TargetTwoID: {0}"), FText::AsNumber(0));

	if (bInReverseGear == true)
	{
		GearDisplayString = FText(LOCTEXT("ReverseGear", "R"));
	}
	else
	{
		int32 Gear = GetVehicleMovement()->GetCurrentGear();
		GearDisplayString = (Gear == 0) ? LOCTEXT("N", "N") : FText::AsNumber(Gear);
	}	
}
#undef LOCTEXT_NAMESPACE
	