// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PredatorAnimal.h"
#include "Lion.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API ALion : public APredatorAnimal
{
	GENERATED_BODY()

public:
	ALion();

protected:
	// 충돌 감지를 위한 박스 컴포넌트
	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionBox;

	class ULionAnim* LionAnim;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

};
