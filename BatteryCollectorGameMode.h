// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"

// Enum to store current gameplay state
UENUM(BlueprintType)
enum class EBatteryPlayState{

	Playing,
	GameOver,
	Won,
	Unknown

};


UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float deltaTime) override;

	// Return the needed power to win the game
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin();

	virtual void BeginPlay() override;

	// State manipulation functions
	UFUNCTION(BlueprintPure, Category = "GameState")
	EBatteryPlayState GetCurPlayState();
	void SetCurPlayState(EBatteryPlayState newState);

protected:
	// Rate at which the char's power decays
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float decayRate;

	// Power necessary to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float powerToWin;

	// Widget class for HUD screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> gameHUDWidgetClass;

	// Instance of the above HUD
	UPROPERTY()
	class UUserWidget* currentWidget;

private:
	EBatteryPlayState curPlayState;

	TArray<class ASpawnVolume*> spawnVolumeActors;

	// Handle any function calls that rely upon changing the playing state of our game
	void HandleNewState(EBatteryPlayState newState);

};
