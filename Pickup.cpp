// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// All pickups start active
	isActive = true;

	// Create Static Mesh Component
	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pickupMesh"));
	RootComponent = pickupMesh;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	// Registers with scene and does other "setup" functions
	Super::BeginPlay();

}

// ---------------------------------------------------------------------------------------------------------------------
// IsActive
//   input
//     None
//   return
//     Boolean describing the state of the pickup
//
// ---------------------------------------------------------------------------------------------------------------------
bool APickup::IsActive(){
	return isActive;
}

// ---------------------------------------------------------------------------------------------------------------------
// SetActive
//   input
//     bool newPickupState - the new state of the pickup
//   return
//     None
//
// ---------------------------------------------------------------------------------------------------------------------
void APickup::SetActive(bool newPickupState){
	isActive = newPickupState;
}


void APickup::CollectPickup_Implementation(){

	// Log debug
	FString pickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *pickupDebugString)

}
