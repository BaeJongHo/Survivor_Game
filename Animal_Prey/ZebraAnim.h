// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnimalAnim.h"
#include "ZebraAnim.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UZebraAnim : public UAnimalAnim
{
	GENERATED_BODY()

public:
	UZebraAnim();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
