// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Animation/AnimInstance.h"
#include "AnimalAnim.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EAnimalAnim : uint8
{
	Idle,
	Walk,
	Run,
	Hit,
	Attack,
	Death
};

UCLASS()
class SURVIVAL_IN_AFRICA_API UAnimalAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimalAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EAnimalAnim"))
	uint8 AnimType;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void SetAnimType(EAnimalAnim eAnimType);

public:
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();
	
	UFUNCTION()
	void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();
};
