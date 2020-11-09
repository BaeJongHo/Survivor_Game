// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "PlayerSurvivor.h"
#include "SurvivorController.h"
#include "UISurvivorState.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerSurvivor> PlayerClass(TEXT("Blueprint'/Game/Player/BPPlayerSurvivor.BPPlayerSurvivor_C'"));

	if (PlayerClass.Succeeded())
		DefaultPawnClass = PlayerClass.Class;

	static ConstructorHelpers::FClassFinder<ASurvivorController> ControllerClass(TEXT("Blueprint'/Game/Player/BPSurvivorController.BPSurvivorController_C'"));
	
	if (ControllerClass.Succeeded())
		PlayerControllerClass = ControllerClass.Class;
}
