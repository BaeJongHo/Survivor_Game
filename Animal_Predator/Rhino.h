// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PredatorAnimal.h"
#include "Rhino.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API ARhino : public APredatorAnimal
{
	GENERATED_BODY()

public:
	ARhino();

protected:
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	class URhinoAnim* RhinoAnim;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

};
