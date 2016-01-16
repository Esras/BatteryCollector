// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 *
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup{

	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABatteryPickup();

	// Override the collection function - using implemention because it's a blueprint native event
	void CollectPickup_Implementation() override;

	float GetPower();

protected:
	// Amount of power the battery pickup gives to the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected))
	float batteryPower;

};
