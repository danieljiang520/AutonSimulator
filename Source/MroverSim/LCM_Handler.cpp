// Fill out your copyright notice in the Description page of Project Settings.


#include "LCM_Handler.h"

LCM_Handler::LCM_Handler(){}

LCM_Handler::~LCM_Handler(){}

void LCM_Handler::handleGPS(const lcm::ReceiveBuffer* rbuf,
					        const std::string& chan, 
			                const rover_msgs::GPS* msg)
{
	UE_LOG(LogTemp, Display, TEXT("LCM: Received message on channel GPS"));
    UE_LOG(LogTemp, Display, TEXT("LCM: Here is my speed: %f"), msg->speed);
}
