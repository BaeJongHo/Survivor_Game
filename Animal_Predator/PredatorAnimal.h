// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animal.h"
#include "PredatorAnimal.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API APredatorAnimal : public AAnimal
{
	GENERATED_BODY()

public:
	APredatorAnimal();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
};
