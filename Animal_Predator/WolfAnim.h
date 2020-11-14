// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimalAnim.h"
#include "WolfAnim.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UWolfAnim : public UAnimalAnim
{
	GENERATED_BODY()

public:
	UWolfAnim();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
