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
const float maxSpeed = 1.6; //KPH

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
	Camera1 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera1->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera1->bUsePawnControlRotation = false;
	Camera1->FieldOfView = 90.f;

	// Create second camera component
	Camera2 = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera2"));


	currentCamera_index = 1;
}
	void AMroverSimPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMroverSimPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMroverSimPawn::MoveRight);
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AMroverSimPawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AMroverSimPawn::OnHandbrakeReleased);

	// binding key to switch cameras
	PlayerInputComponent->BindAction("ChangeCameras", IE_Pressed, this, &AMroverSimPawn::changeCameras);
}

void AMroverSimPawn::MoveForward(float Val)
{
	leftControllerAxis = Val;
}

void AMroverSimPawn::MoveRight(float Val)
{
	rightControllerAxis = Val;
}

void AMroverSimPawn::OnHandbrakePressed()
{
	VehicleSimple->SetBrakeTorque(1000, FRONT_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(1000, FRONT_RIGHT_WHEEL);
	VehicleSimple->SetBrakeTorque(1000, BACK_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(1000, BACK_RIGHT_WHEEL);
}

void AMroverSimPawn::OnHandbrakeReleased()
{
	VehicleSimple->SetBrakeTorque(0, FRONT_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(0, FRONT_RIGHT_WHEEL);
	VehicleSimple->SetBrakeTorque(0, BACK_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(0, BACK_RIGHT_WHEEL);
}

/** Returns Camera subobject **/
int GetCameraIndex() const { 
	return currentCamera_index;
}
int GetNextCameraIndex() const {
	if (GetCameraIndex() == (cameras.size()-1)) { return 0; }
	return GetCameraIndex() + 1; 
}

/** Sets Camera subobject **/
void SetCamera(int camera_index) { 
	for (size_t i = 0; i < cameras.size(); ++i) {
		if (i == camera_index) {
			cameras[i]->Activate(); 
		}
		else {
			cameras[i]->Deactivate(); 
		}
	}
}

void AMroverSimPawn::changeCameras() {
	// if press "c", this function will be called
	// to change variables, do in tick()

	// camera views: 2 => "c" to change to next, "c" to change back 
	// currentCamera default to 1 (ie. first camera view), change would change it to 2

	SetCamera(GetNextCameraIndex()); 

}

void AMroverSimPawn::moveChasis(float leftAxis, float rightAxis) {
	float KPH = GetVehicleMovement()->GetForwardSpeed() * 0.036f; //velocity in KPH
	float torque = 200;
	if(-1 * maxSpeed < KPH && KPH < maxSpeed){ //within speed limit
		torque = 200;
	}else if (leftAxis * KPH < 0.0){ //extra torque for revering when falling downhill 
		torque = 700;
	}else{ //exceeds speed limit
		leftAxis = 0;
	}
	
	float leftVelocity = leftAxis + rightAxis;
	float rightVelocity = leftAxis - rightAxis;

	VehicleSimple->SetDriveTorque(torque * leftVelocity,FRONT_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(torque * rightVelocity,FRONT_RIGHT_WHEEL);
	VehicleSimple->SetDriveTorque(torque * leftVelocity,BACK_LEFT_WHEEL);
	VehicleSimple->SetDriveTorque(torque * rightVelocity,BACK_RIGHT_WHEEL);

	// FString TheFloatStr = FString::SanitizeFloat(rightAxis);
	// GEngine->AddOnScreenDebugMessage( -1,1.0,FColor::Red, *TheFloatStr );

}

void AMroverSimPawn::Tick(float Delta)
{
	Super::Tick(Delta);

	moveChasis(leftControllerAxis, rightControllerAxis);
	
	// Update the strings used in the hud (incar and onscreen)
	UpdateHUDStrings();

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

void AMroverSimPawn::UpdateHUDStrings()
{
	float KPH = GetVehicleMovement()->GetForwardSpeed() * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);

	// Using FText because this is display text that should be localizable
	SpeedDisplayString = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH));

	NavStateStatusDisplayString = FText::Format(LOCTEXT("NavStateFormat", "Navigation State: {0}"), FText::AsNumber(0));

	WaypointsDisplayString = FText::Format(LOCTEXT("WaypointsFormat", "Waypoints: {0}"), FText::AsNumber(0));

	JoystickTranslationalDisplayString = FText::Format(LOCTEXT("JoystickTranslationalFormat", "JoystickTranslational: {0}"), FText::AsNumber(0));

	JoystickRotationalDisplayString = FText::Format(LOCTEXT("JoystickRotationalFormat", "JoystickRotational: {0}"), FText::AsNumber(0));

	OdometryLatitudeDisplayString = FText::Format(LOCTEXT("OdometryLatitudeFormat", "OdometryLatitude: {0}"), FText::AsNumber(0));

	OdometryLongitudeDisplayString = FText::Format(LOCTEXT("OdometryLongitudeFormat", "OdometryLongitude: {0}"), FText::AsNumber(0));

	OdometryHeadingDisplayString = FText::Format(LOCTEXT("OdometryHeadingFormat", "OdometryHeading: {0}"), FText::AsNumber(0));

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
	
