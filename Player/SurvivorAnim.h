// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SurvivorAnim.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EDir : uint8
{
	Front,
	Back,
	Right,
	Left
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EState : uint8
{
	Normal,
	Bow,
	Sword
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class ESurvivorAnim : uint8
{
	Idle,
	Run,
	Jump,
	Attack,
	Pick,
	Death
};

UCLASS()
class SURVIVAL_IN_AFRICA_API USurvivorAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USurvivorAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EDir"))
	uint8 Dir;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EState"))
	uint8 State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "ESurvivorAnim"))
	uint8 AnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "ESurvivorAnim"))
	UAnimMontage* Attack1Montage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "ESurvivorAnim"))
	UAnimMontage* Attack2Montage;

public:
	void SetMoveDir(EDir eDir)
	{
		Dir = (uint8)eDir;
	}

	uint8 GetState() const
	{
		return State;
	}

	void SetState(EState eState)
	{
		State = (uint8)eState;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void SetAnimType(ESurvivorAnim eAnimType);

public:
	UFUNCTION()
	void AnimNotify_JumpEnd();

	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	void Jump();
	void Attack();
};
