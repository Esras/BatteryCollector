// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"


// Sets default values for this actor's properties
ABatteryPickup::ABatteryPickup(){

	// When batteries spawn in, have them fall
	GetMesh()->SetSimulatePhysics(true);

	// Base power of the battery
	batteryPower = 150;

}

void ABatteryPickup::CollectPickup_Implementation(){

	// Use the base pickup behavior
	Super::CollectPickup_Implementation();

	// Now destroy the battery
	Destroy();
}

float ABatteryPickup::GetPower(){
	return batteryPower;
}