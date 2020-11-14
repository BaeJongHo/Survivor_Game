// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PredatorAnimal.h"
#include "Wolf.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API AWolf : public APredatorAnimal
{
	GENERATED_BODY()

public:
	AWolf();

protected:
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	class UWolfAnim* WolfAnim;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

};
