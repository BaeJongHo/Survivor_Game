// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimalAnim.h"
#include "DeerAnim.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UDeerAnim : public UAnimalAnim
{
	GENERATED_BODY()

public:
	UDeerAnim();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
