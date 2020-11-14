// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimalAnim.h"
#include "LionAnim.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API ULionAnim : public UAnimalAnim
{
	GENERATED_BODY()

public:
	ULionAnim();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

};
