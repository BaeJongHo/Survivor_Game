// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimalAnim.h"
#include "PigAnim.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UPigAnim : public UAnimalAnim
{
	GENERATED_BODY()

public:
	UPigAnim();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
