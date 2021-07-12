// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "SimpleWheeledVehicleMovementComponent.h"
#include "MroverSimPawnAuto.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class UInputComponent;

UCLASS(config=Game)
class AMroverSimPawnAuto : public AWheeledVehicle
{
	GENERATED_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	/** SCene component for the In-Car view origin */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* InternalCameraBase;

	/** Camera component for the In-Car view */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* InternalCamera;

	/** Text component for the In-Car speed */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* InCarSpeed;

	/** Text component for the In-Car gear */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* InCarGear;

	/** Text component for the NavStateStatus */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* NavStateStatus;

	/** Text component for the Waypoints */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* Waypoints;

	/** Text component for the JoystickTranslational */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* JoystickTranslational;

	/** Text component for JoystickRotational */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* JoystickRotational;

	/** Text component for the OdometryLatitude */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* OdometryLatitude;

	/** Text component for the OdometryLongitude */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* OdometryLongitude;

	/** Text component for the OdometryHeading */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* OdometryHeading;

	/** Text component for the ObstacleDistance */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* ObstacleDistance;

	/** Text component for the ObstacleBearing */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* ObstacleBearing;

	/** Text component for the RadioStrength */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* RadioStrength;

	/** Text component for the TargetOneDistance */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TargetOneDistance;

	/** Text component for the TargetOneBearing */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TargetOneBearing;

	/** Text component for the TargetOneID */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TargetOneID;

	/** Text component for the TargetTwoDistance */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TargetTwoDistance;

	/** Text component for the TargetTwoBearing */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TargetTwoBearing;

	/** Text component for the TargetTwoID */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TargetTwoID;


	
public:
	AMroverSimPawnAuto();

	AMroverSimPawnAuto(const class FObjectInitializer& PCIP);

	/** The current speed as a string eg 10 km/h */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText SpeedDisplayString;

	/** The current gear as a string (R,N, 1,2 etc) */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText GearDisplayString;

		/** Text component for the NavStateStatus */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText NavStateStatusDisplayString;

	/** Location of NavStateStatus Text */
	UPROPERTY(Category = Display, EditAnywhere, BlueprintReadWrite)
	FVector NavStateStatusLocation = {66.0f, -9.0f, 95.0f};

	/** Text component for the Waypoints */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText WaypointsDisplayString;

	/** Text component for the JoystickTranslational */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText JoystickTranslationalDisplayString;

	/** Text component for JoystickRotational */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText JoystickRotationalDisplayString;

	/** Text component for the OdometryLatitude */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText OdometryLatitudeDisplayString;

	/** Text component for the OdometryLongitude */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText OdometryLongitudeDisplayString;

	/** Text component for the OdometryHeading */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText OdometryHeadingDisplayString;

	/** Text component for the ObstacleDistance */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText ObstacleDistanceDisplayString;

	/** Text component for the ObstacleBearing */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText ObstacleBearingDisplayString;

	/** Text component for the RadioStrength */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText RadioStrengthDisplayString;

	/** Text component for the TargetOneDistance */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText TargetOneDistanceDisplayString;

	/** Text component for the TargetOneBearing */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText TargetOneBearingDisplayString;

	/** Text component for the TargetOneID */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText TargetOneIDDisplayString;

	/** Text component for the TargetTwoDistance */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText TargetTwoDistanceDisplayString;

	/** Text component for the TargetTwoBearing */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText TargetTwoBearingDisplayString;

	/** Text component for the TargetTwoID */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FText TargetTwoIDDisplayString;

	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	/** The color of the incar gear text in forward gears */
	FColor	GearDisplayColor;

	/** The color of the incar gear text when in reverse */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
	FColor	GearDisplayReverseColor;

	/** Are we using incar camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInCarCameraActive;

	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
	bool bInReverseGear;

	/** Initial offset of incar camera */
	FVector InternalCameraOrigin;
	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;
protected:
	virtual void BeginPlay() override;

public:

	// Wheel Numbering
	const static int FRONT_LEFT_WHEEL = 0;
	const static int FRONT_RIGHT_WHEEL = 1;
	const static int BACK_LEFT_WHEEL = 2;
	const static int BACK_RIGHT_WHEEL = 3;

	void AutoMove();

	void moveChasis(float leftAxis, float rightAxis);

	/** Handle moving forward */
	void MoveForward(float Val);

	/** Handle turning right */
	void MoveRight(float Val);

	void GoForward();
	void GoRight();
	//void LineTrace();

	/** Handle handbrake pressed */
	void Brake();
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();

	/** Update the physics material used by the vehicle mesh */
	void UpdatePhysicsMaterial();

	static const FName LookUpBinding;
	static const FName LookRightBinding;

private:

	/** Update the gear and speed strings */
	void UpdateHUDStrings();

	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;

	USimpleWheeledVehicleMovementComponent* VehicleSimple;

	float leftControllerAxis;
	float rightControllerAxis;

	bool frontHitSomething;

	float testAxis;
	float testRAxis;

	FVector2D dest;
	float destAngle;
	bool isGoForwardCalled;
	bool isGoRightCalled;


public:
	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

	/** Returns InCarSpeed subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarSpeed() const { return InCarSpeed; }

public:
	/** Setting up box for detecting obstacles **/
	/** The Height of my Sphere starting from the location of the Actor **/
	UPROPERTY(EditAnywhere, Category = "Sweep")
	float SphereHeight = 200;

	/** The Radius of the sphere trace **/
	UPROPERTY(EditAnywhere, Category = "Sweep")
	float SphereRadius = 500;

	/** Sphere segments - used for visualization only **/
	UPROPERTY(EditAnywhere, Category = "Sweep")
	int32 Segments = 100;
};
