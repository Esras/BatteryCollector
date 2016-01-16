// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Grab the spawn volume publicly
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return whereToSpawn; }

	// Get a random point in the volume and return it
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetActive(bool newSpawnState);

	UFUNCTION(BlueprintPure, Category = "Spawning")
	bool IsActive();

protected:
	// Which pickup the volume will spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> whatToSpawn;


	FTimerHandle spawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float spawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float spawnDelayRangeHigh;


private:
	// Box component to specify where pickups spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* whereToSpawn;

	// Handle spawning a new pickup
	void SpawnPickup();
	float GetNewSpawnDelay();

	float spawnDelay;

	bool spawnActive;

};
