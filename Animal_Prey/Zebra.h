// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreyAnimal.h"
#include "Zebra.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API AZebra : public APreyAnimal
{
	GENERATED_BODY()

public:
	AZebra();

protected:
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	class UZebraAnim* ZebraAnim;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

};
