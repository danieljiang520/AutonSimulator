// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimPawnAuto.h"
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
#include "DrawDebugHelpers.h"
#include "Math/Quat.h"

#ifndef HMD_MODULE_INCLUDED
#define HMD_MODULE_INCLUDED 0
#endif

// Needed for VR Headset
#if HMD_MODULE_INCLUDED
#include "IXRTrackingSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#endif // HMD_MODULE_INCLUDED

const FName AMroverSimPawnAuto::LookUpBinding("LookUp");
const FName AMroverSimPawnAuto::LookRightBinding("LookRight");
const float maxSpeed = 1.6; //KPH

#define LOCTEXT_NAMESPACE "VehiclePawn"

AMroverSimPawnAuto::AMroverSimPawnAuto(const class FObjectInitializer& PCIP) :
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
void AMroverSimPawnAuto::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMroverSimPawnAuto::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMroverSimPawnAuto::MoveRight);
	PlayerInputComponent->BindAxis("GoForward", this, &AMroverSimPawnAuto::GoForward);
	//PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AMroverSimPawnAuto::OnHandbrakePressed);
	//PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AMroverSimPawnAuto::OnHandbrakeReleased);
}

void AMroverSimPawnAuto::MoveForward(float Val)
{
	leftControllerAxis = Val;
}

void AMroverSimPawnAuto::MoveRight(float Val)
{
	rightControllerAxis = Val;
}

void AMroverSimPawnAuto::GoForward(float Val)//Val = -1,0,or 1
{	
	if (Val == 1){
		float distance = 10; // test variable
		//forward if leftAxis 1, backward if -1
		float forwardAxis;
		FVector location = GetActorLocation();
		if(location.X < location.X + distance){
			forwardAxis = 0.9;
			moveChasis(forwardAxis,0);
		}
		else {
			forwardAxis = -0.9;
			moveChasis(forwardAxis,0);
		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("Left axis: %f"), forwardAxis));
	}
	
}

void AMroverSimPawnAuto::GoRight(float distance)
{
	//forward if leftAxis 1, backward if -1
	// float rightAxis;
	// if(GetActorLocation()< ){
	// 	rightAxis = 1;
	// 	moveChasis(rightAxis,0);
	// }
	// else {
	// 	rightAxis = -1;
	// 	moveChasis(rightAxis,0);
	// }
}

void AMroverSimPawnAuto::Brake()
{
	VehicleSimple->SetBrakeTorque(1000, FRONT_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(1000, FRONT_RIGHT_WHEEL);
	VehicleSimple->SetBrakeTorque(1000, BACK_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(1000, BACK_RIGHT_WHEEL);
}
/*
void AMroverSimPawnAuto::OnHandbrakeReleased()
{
	VehicleSimple->SetBrakeTorque(0, FRONT_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(0, FRONT_RIGHT_WHEEL);
	VehicleSimple->SetBrakeTorque(0, BACK_LEFT_WHEEL);
	VehicleSimple->SetBrakeTorque(0, BACK_RIGHT_WHEEL);
}*/

void AMroverSimPawnAuto::moveChasis(float leftAxis, float rightAxis) {
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

	FString TheFloatStr = FString::SanitizeFloat(leftAxis);
	GEngine->AddOnScreenDebugMessage( -1,1.0,FColor::Yellow, *TheFloatStr );

}

void AMroverSimPawnAuto::Tick(float Delta)
{
	Super::Tick(Delta);

	float forwardSpeed = GetVehicleMovement()->GetForwardSpeed(); //velocity in KPH

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("Velocity: %f"), forwardSpeed));
	
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
	

// 	/*TArray is the collection that contains all the HitResults*/
//     TArray<FHitResult> HitResults;

//     /*The Start location of the sphere*/
//     FVector StartLocation = GetActorLocation() + SphereRadius;
 
//     /*The End location of the sphere is equal to the default location of the actor plus the height we will enter from the editor
//     To extend this functionality, you can replace the height variable with a FVector*/
//     FVector EndLocation = GetActorLocation();
//     EndLocation.Z += SphereHeight;
 
//     /*Search for static objects only*/
//     ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;
 
//     /*Declare the Collision Shape, assign a Sphere shape and set radius*/
//     FCollisionShape CollisionShape;
//     CollisionShape.ShapeType = ECollisionShape::Sphere;
//     CollisionShape.SetSphere(SphereRadius);
 
//     /*Perform the actual raycast. This method returns true if there is at least 1 hit.*/
//     bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::Identity, ECC_WorldStatic, CollisionShape);
 
//     /*If the raycast hit a number of objects, iterate through them and print their name in the console*/
//     if (bHitSomething)
//     {
//         /*for (auto It = HitResults.CreateIterator(); It; It++)
//         {
//             GLog->Log((*It).Actor->GetName());
//         }*/

// 		if (GEngine) {
// 			for (auto& Hit : HitResults) {
// 			    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *Hit.GetActor()->GetName()));
// 			    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *Hit.ImpactPoint.ToString()));
//                 GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *Hit.ImpactNormal.ToString()));
// 			}

//             }
//     }
 
//     /*In order to draw the sphere of the first image, I will use the DrawDebugSphere function which resides in the DrawDebugHelpers.h
//     This function needs the center of the sphere which in this case is provided by the following equation*/
//     FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;
 
//     /*Draw the sphere in the viewport*/
//     DrawDebugSphere(GetWorld(), CenterOfSphere, CollisionShape.GetSphereRadius(), Segments, FColor::Green, true); 
}

void AMroverSimPawnAuto::BeginPlay() 
{ 
	Super::BeginPlay();  

}

void AMroverSimPawnAuto::UpdateHUDStrings()
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
	
