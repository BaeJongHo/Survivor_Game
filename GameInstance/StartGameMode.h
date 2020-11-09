// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	TSubclassOf<UUserWidget> StartLevelWidgetClass;
	class UStartLevelWidget* StartLevelWidget;
	
public:
	AStartGameMode();

public:
	virtual void BeginPlay();
};
