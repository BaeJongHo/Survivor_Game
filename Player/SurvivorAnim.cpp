// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorAnim.h"
#include "PlayerSurvivor.h"

USurvivorAnim::USurvivorAnim()
{
	Dir = (uint8)EDir::Front;
	State = (uint8)EState::Normal;
	AnimType = (uint8)ESurvivorAnim::Idle;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack1Asset(TEXT("AnimMontage'/Game/Player/MTGSwordAttack.MTGSwordAttack'"));

	if (Attack1Asset.Succeeded())
		Attack1Montage = Attack1Asset.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack2Asset(TEXT("AnimMontage'/Game/Player/MTGBowAttack.MTGBowAttack'"));

	if (Attack2Asset.Succeeded())
		Attack2Montage = Attack2Asset.Object;
}

void USurvivorAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USurvivorAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerSurvivor* pOwner = Cast<APlayerSurvivor>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		UCharacterMovementComponent* pMovement = pOwner->GetCharacterMovement();

		if (IsValid(pMovement))
		{
			if (pMovement->IsMovingOnGround())
			{
				if (pMovement->Velocity.Size() > 0.f)
				{
					AnimType = (uint8)ESurvivorAnim::Run;
				}
				else
				{
					if (AnimType != (uint8)ESurvivorAnim::Death)
						AnimType = (uint8)ESurvivorAnim::Idle;
				}
			}
		}
	}
}

void USurvivorAnim::SetAnimType(ESurvivorAnim eAnimType)
{
	AnimType = (uint8)eAnimType;
}

void USurvivorAnim::AnimNotify_JumpEnd()
{
	AnimType = (uint8)ESurvivorAnim::Idle;
}

void USurvivorAnim::AnimNotify_AttackStart()
{
	APlayerSurvivor* pOwner = Cast<APlayerSurvivor>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->EnableWeaponCollision(true);
}

void USurvivorAnim::AnimNotify_AttackEnd()
{
	AnimType = (uint8)ESurvivorAnim::Idle;

	APlayerSurvivor* pOwner = Cast<APlayerSurvivor>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->EnableWeaponCollision(false);
		pOwner->SetBeginOverlapEnable(true);
	}
}

void USurvivorAnim::Jump()
{
	AnimType = (uint8)ESurvivorAnim::Jump;
}

void USurvivorAnim::Attack()
{
	if (!Montage_IsPlaying(Attack1Montage) && State == (uint8)EState::Sword)
		Montage_Play(Attack1Montage);

	else if (!Montage_IsPlaying(Attack2Montage) && State == (uint8)EState::Bow)
		Montage_Play(Attack2Montage);
}

