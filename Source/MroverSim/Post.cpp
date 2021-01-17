#include "Post.h"

// Sets default values
APost::APost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(!lcm.good()) {
        UE_LOG(LogTemp, Error, TEXT("LCM no work :("));
    } else {
		UE_LOG(LogTemp, Display, TEXT("LCM Initialized"));
	}

    lcm.subscribe("/gps", &LCM_Handler::handleGPS, &handlerObject);
}

// Called when the game starts or when spawned
void APost::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rover_msgs::GPS gps_struct = rover_msgs::GPS();
	gps_struct.latitude_deg = 1;
	gps_struct.latitude_min = 2;
	gps_struct.longitude_deg = 3;
	gps_struct.longitude_min = 4;
	gps_struct.bearing_deg = 5;
	gps_struct.speed = 6;

	// This publishes an lcm message to be recieved by any subscribing processes
	lcm.publish("/gps", &gps_struct);

	// This runs the lcm loop for up to 10ms so incoming messages can be handled
	lcm.handleTimeout(10);

}

