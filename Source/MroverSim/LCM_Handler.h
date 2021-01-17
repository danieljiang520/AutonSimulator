// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

THIRD_PARTY_INCLUDES_START
#include <lcm/lcm-cpp.hpp>
#include <lcm/rover_msgs/GPS.hpp>
THIRD_PARTY_INCLUDES_END

class LCM_Handler
{
	public:
	LCM_Handler();
	~LCM_Handler();
	void handleGPS(const lcm::ReceiveBuffer* rbuf,
				   const std::string& chan, 
			       const rover_msgs::GPS* msg);
};