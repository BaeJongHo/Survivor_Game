// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimalAnim.h"
#include "RhinoAnim.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API URhinoAnim : public UAnimalAnim
{
	GENERATED_BODY()

public:
	URhinoAnim();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	
};
