// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the box component to represent spawn volume
	whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("whereToSpawn"));
	RootComponent = whereToSpawn;

	spawnDelayRangeLow  = 1.0f;
	spawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay(){

	Super::BeginPlay();

}


// Called every frame
void ASpawnVolume::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


FVector ASpawnVolume::GetRandomPointInVolume(){

	FVector spawnOrigin = whereToSpawn->Bounds.Origin;
	FVector spawnExtent = whereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);

}


float ASpawnVolume::GetNewSpawnDelay(){

	return FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);

}


void ASpawnVolume::SetActive(bool newSpawnState){

	spawnActive = newSpawnState;

	if(spawnActive){
		spawnDelay = GetNewSpawnDelay();
		GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, spawnDelay, false);
	} else {
		GetWorldTimerManager().ClearTimer(spawnTimer);
	}

}


bool ASpawnVolume::IsActive(){
	return spawnActive;
}


void ASpawnVolume::SpawnPickup(){

	// Check if we have set something to spawn
	if(whatToSpawn != NULL){

		// Check for a valid world
		UWorld* const world = GetWorld();
		if(world){

			// Set the spawn parameters
			FActorSpawnParameters spawnParams;
			spawnParams.Owner      = this;
			spawnParams.Instigator = Instigator;

			// Give some values for where and how the pickup will spawn
			FVector spawnLocation = GetRandomPointInVolume();
			FRotator spawnRotation;
			spawnRotation.Yaw   = FMath::FRand() * 360.0f;
			spawnRotation.Pitch = FMath::FRand() * 360.0f;
			spawnRotation.Roll  = FMath::FRand() * 360.0f;

			// Spawn the pickup
			APickup* const spawnedPickup = world->SpawnActor<APickup>(whatToSpawn, spawnLocation, spawnRotation, spawnParams);

			// Reset the timer
			spawnDelay = GetNewSpawnDelay();
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, spawnDelay, false);

		}
	}
}