// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"


ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Base decay rate
	decayRate = 250.0;
}


void ABatteryCollectorGameMode::BeginPlay(){

	Super::BeginPlay();

	// Find all of the spawn volumes
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), foundActors);

	for(auto actor : foundActors){
		ASpawnVolume* spawnVolume = Cast<ASpawnVolume>(actor);
		if(spawnVolume){
			spawnVolumeActors.AddUnique(spawnVolume);
		}
	}

	SetCurPlayState(EBatteryPlayState::Playing);

	// Set the win condition
	ABatteryCollectorCharacter* playerChar = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(playerChar){
		powerToWin = playerChar->GetInitialPower() * 1.25; // Tweak based on difficulty
	}

	// Set up our HUD
	if(gameHUDWidgetClass != nullptr){
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), gameHUDWidgetClass);
		if(currentWidget != nullptr){
			currentWidget->AddToViewport();
		}
	}

}


void ABatteryCollectorGameMode::Tick(float deltaTime){

	Super::Tick(deltaTime);

	// Cast and check that the cast succeeded
	ABatteryCollectorCharacter* playerChar = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(playerChar){
		float curPlayerPower = playerChar->GetCurPower();

		if(curPlayerPower > powerToWin){
			SetCurPlayState(EBatteryPlayState::Won);
		} else if(curPlayerPower > 0){
			playerChar->PowerChange(-1 * deltaTime * decayRate);
		} else {
			SetCurPlayState(EBatteryPlayState::GameOver);
		}
	}

}


float ABatteryCollectorGameMode::GetPowerToWin(){
	return powerToWin;
}


EBatteryPlayState ABatteryCollectorGameMode::GetCurPlayState(){
	return curPlayState;
}


void ABatteryCollectorGameMode::SetCurPlayState(EBatteryPlayState newState){
	curPlayState = newState;
	HandleNewState(curPlayState);
}


void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState newState){

	bool spawnsActive = false;

	switch(newState){
		case EBatteryPlayState::Playing:
			// Make spawn volumes active
			spawnsActive = true;
			break;
		case EBatteryPlayState::Won:
			// Spawns inactive
			spawnsActive = false;
			break;
		case EBatteryPlayState::GameOver:{
			// Spawns inactive
			spawnsActive = false;

			// Block player input
			APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
			if(playerController){
				playerController->SetCinematicMode(true, false, false, true, true);
			}

			// Ragdoll player
			ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
			if(playerCharacter){
				// This is commented out because the tutorial has some differences in versions for collision.  I already
				// had to make a blueprint for the chracter (different than the tutorial) so something is happening
				// here where it won't accept the collision model for the skeleton, so it's commented out.
				//playerCharacter->GetMesh()->SetSimulatePhysics(true);
				playerCharacter->GetMovementComponent()->MovementState.bCanJump = false;
			}

			break;
		}
		case EBatteryPlayState::Unknown:
		default:
			spawnsActive = false;
			// STUFF BE BROKE, YO!
			break;
	}

	for(ASpawnVolume* volume : spawnVolumeActors){
		volume->SetActive(spawnsActive);
	}

}