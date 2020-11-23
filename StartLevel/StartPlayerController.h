// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "StartPlayerController.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API AStartPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStartPlayerController();

private:
	TSubclassOf<UUserWidget> MouseWidgetClass;
	UUserWidget* MouseWidget;

private:
	virtual void BeginPlay();
};
