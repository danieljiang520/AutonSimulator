// Copyright Epic Games, Inc. All Rights Reserved.

#include "MroverSimPawn.h"
#include "MroverSimWheelFront.h"
#include "MroverSimWheelRear.h"
#include "MroverSimHud.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
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

AMroverSimPawn::AMroverSimPawn()
{
	// Car mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/Vehicle/Sedan/Sedan_SkelMesh.Sedan_SkelMesh"));
	GetMesh()->SetSkeletalMesh(CarMesh.Object);

	static ConstructorHelpers::FClassFinder<UObject> AnimBPClass(TEXT("/Game/Vehicle/Sedan/Sedan_AnimBP"));
	GetMesh()->SetAnimInstanceClass(AnimBPClass.Class);
	
	// Simulation
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	check(Vehicle4W->WheelSetups.Num() == 4);

	Vehicle4W->WheelSetups[0].WheelClass = UMroverSimWheelFront::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("Wheel_Front_Left");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = UMroverSimWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("Wheel_Front_Right");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	Vehicle4W->WheelSetups[2].WheelClass = UMroverSimWheelRear::StaticClass();
	Vehicle4W->WheelSetups[2].BoneName = FName("Wheel_Rear_Left");
	Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[3].WheelClass = UMroverSimWheelRear::StaticClass();
	Vehicle4W->WheelSetups[3].BoneName = FName("Wheel_Rear_Right");
	Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, 12.f, 0.f);

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

	// Create In-Car camera component 
	InternalCameraOrigin = FVector(0.0f, -40.0f, 120.0f);

	InternalCameraBase = CreateDefaultSubobject<USceneComponent>(TEXT("InternalCameraBase"));
	InternalCameraBase->SetRelativeLocation(InternalCameraOrigin);
	InternalCameraBase->SetupAttachment(GetMesh());

	InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	InternalCamera->bUsePawnControlRotation = false;
	InternalCamera->FieldOfView = 90.f;
	InternalCamera->SetupAttachment(InternalCameraBase);

	//Setup TextRenderMaterial
	static ConstructorHelpers::FObjectFinder<UMaterial> TextMaterial(TEXT("Material'/Engine/EngineMaterials/AntiAliasedTextMaterialTranslucent.AntiAliasedTextMaterialTranslucent'"));
	
	UMaterialInterface* Material = TextMaterial.Object;

	// Create text render component for in car speed display
	InCarSpeed = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	InCarSpeed->SetTextMaterial(Material);
	InCarSpeed->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	InCarSpeed->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	InCarSpeed->SetupAttachment(GetMesh());
	InCarSpeed->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

	// Create text render component for Nav State display
	NavStateStatus = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NavStateStatus"));
	NavStateStatus->SetTextMaterial(Material);
	NavStateStatus->SetRelativeLocation(NavStateStatusLocation);
	NavStateStatus->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	NavStateStatus->SetupAttachment(GetMesh());
	NavStateStatus->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

/*	// Create text render component for in car speed display
	JoystickTranslational = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Waypoints"));
	JoystickTranslational->SetTextMaterial(Material);
	JoystickTranslational->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	JoystickTranslational->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	JoystickTranslational->SetupAttachment(GetMesh());
	JoystickTranslational->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

	JoystickRotational = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	JoystickRotational->SetTextMaterial(Material);
	JoystickRotational->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	JoystickRotational->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	JoystickRotational->SetupAttachment(GetMesh());
	JoystickRotational->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

	OdometryLatitude = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	OdometryLatitude->SetTextMaterial(Material);
	OdometryLatitude->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	OdometryLatitude->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	OdometryLatitude->SetupAttachment(GetMesh());
	OdometryLatitude->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

	OdometryLongitude = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	OdometryLongitude->SetTextMaterial(Material);
	OdometryLongitude->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	OdometryLongitude->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	OdometryLongitude->SetupAttachment(GetMesh());
	OdometryLongitude->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

	OdometryHeading = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	OdometryHeading->SetTextMaterial(Material);
	OdometryHeading->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	OdometryHeading->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	OdometryHeading->SetupAttachment(GetMesh());
	OdometryHeading->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));

	InCarSpeed = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	InCarSpeed->SetTextMaterial(Material);
	InCarSpeed->SetRelativeLocation(FVector(70.0f, -75.0f, 99.0f));
	InCarSpeed->SetRelativeRotation(FRotator(18.0f, 180.0f, 0.0f));
	InCarSpeed->SetupAttachment(GetMesh());
	InCarSpeed->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));
*/
	// Create text render component for in car gear display
	InCarGear = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	InCarGear->SetTextMaterial(Material);
	InCarGear->SetRelativeLocation(FVector(66.0f, -9.0f, 95.0f));	
	InCarGear->SetRelativeRotation(FRotator(25.0f, 180.0f,0.0f));
	InCarGear->SetRelativeScale3D(FVector(1.0f, 0.4f, 0.4f));
	InCarGear->SetupAttachment(GetMesh());
	
	// Colors for the incar gear display. One for normal one for reverse
	GearDisplayReverseColor = FColor(255, 0, 0, 255);
	GearDisplayColor = FColor(255, 255, 255, 255);

	// Colors for the in-car gear display. One for normal one for reverse
	GearDisplayReverseColor = FColor(255, 0, 0, 255);
	GearDisplayColor = FColor(255, 255, 255, 255);

	bInReverseGear = false;
}

void AMroverSimPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMroverSimPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMroverSimPawn::MoveRight);
	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AMroverSimPawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AMroverSimPawn::OnHandbrakeReleased);
	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AMroverSimPawn::OnToggleCamera);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMroverSimPawn::OnResetVR); 
}

void AMroverSimPawn::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void AMroverSimPawn::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void AMroverSimPawn::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AMroverSimPawn::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AMroverSimPawn::OnToggleCamera()
{
	EnableIncarView(!bInCarCameraActive);
}

void AMroverSimPawn::EnableIncarView(const bool bState, const bool bForce)
{
	if ((bState != bInCarCameraActive) || ( bForce == true ))
	{
		bInCarCameraActive = bState;
		
		if (bState == true)
		{
			OnResetVR();
			Camera->Deactivate();
			InternalCamera->Activate();
		}
		else
		{
			InternalCamera->Deactivate();
			Camera->Activate();
		}
		
		InCarSpeed->SetVisibility(bInCarCameraActive);
		InCarGear->SetVisibility(bInCarCameraActive);
	}
}


void AMroverSimPawn::Tick(float Delta)
{
	Super::Tick(Delta);

	// Setup the flag to say we are in reverse gear
	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;
	
	// Update the strings used in the hud (incar and onscreen)
	UpdateHUDStrings();

	// Set the string in the incar hud
	SetupInCarHUD();

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

	bool bEnableInCar = false;
#if HMD_MODULE_INCLUDED
	bEnableInCar = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
#endif // HMD_MODULE_INCLUDED
	EnableIncarView(bEnableInCar,true);
}

void AMroverSimPawn::OnResetVR()
{
#if HMD_MODULE_INCLUDED
	if (GEngine->XRSystem.IsValid())
	{
		GEngine->XRSystem->ResetOrientationAndPosition();
		InternalCamera->SetRelativeLocation(InternalCameraOrigin);
		GetController()->SetControlRotation(FRotator());
	}
#endif // HMD_MODULE_INCLUDED
}

void AMroverSimPawn::UpdateHUDStrings()
{
	float KPH = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);

	// Using FText because this is display text that should be localizable
	SpeedDisplayString = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH_int));

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

void AMroverSimPawn::SetupInCarHUD()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if ((PlayerController != nullptr) && (InCarSpeed != nullptr) && (InCarGear != nullptr) )
	{
		// Setup the text render component strings
		InCarSpeed->SetText(SpeedDisplayString);
		InCarGear->SetText(GearDisplayString);
		
		if (bInReverseGear == false)
		{
			InCarGear->SetTextRenderColor(GearDisplayColor);
		}
		else
		{
			InCarGear->SetTextRenderColor(GearDisplayReverseColor);
		}
	}
}

#undef LOCTEXT_NAMESPACE
