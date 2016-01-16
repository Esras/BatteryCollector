// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
// Build looks for the generated last in the list, add other headers above this
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Return the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return pickupMesh; }

	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool newPickupState);

	UFUNCTION(BlueprintNativeEvent)
	void CollectPickup();
	virtual void CollectPickup_Implementation();

	// See the Pickup.cpp file
	// // Called every frame
	// virtual void Tick( float DeltaSeconds ) override;

protected:
	// True when pickup can be used, false when deactivated
	bool isActive;

private:
	// Static mesh to represent the pickup in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* pickupMesh;


};
