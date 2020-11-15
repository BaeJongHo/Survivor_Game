// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreyAnimal.h"
#include "Deer.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API ADeer : public APreyAnimal
{
	GENERATED_BODY()

public:
	ADeer();

protected:
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	class UDeerAnim* DeerAnim;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
};
