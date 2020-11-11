// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalAnim.h"
#include "Animal.h"

UAnimalAnim::UAnimalAnim()
{
	AnimType = (uint8)EAnimalAnim::Idle;
}

void UAnimalAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnimalAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 자신이 가지고 있는 몬스터 객체를 가져온다
	AAnimal* pOwner = Cast<AAnimal>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		// 몬스터 객체의 움직임을 얻어온다
		UCharacterMovementComponent* pMovement = pOwner->GetCharacterMovement();

		if (IsValid(pMovement))
		{
			// 몬스터가 땅 위에 있는지 판단한다
			if (pMovement->IsMovingOnGround())
			{
				// pMovement의 사이즈를 통해 몬스터가 움직이고 있는지 판단한다
				if (pMovement->Velocity.Size() > 0.f)
				{
				}
				else
				{
				}
			}
		}
	}
}

void UAnimalAnim::SetAnimType(EAnimalAnim eAnimType)
{
	AnimType = (uint8)eAnimType;
}

// 공격이 시작할 때 호출되는 노티파이 함수
void UAnimalAnim::AnimNotify_AttackStart()
{
	AAnimal* pOwner = Cast<AAnimal>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->EnableAttackCollision(true);
}

// 공격이 끝날 때 호출되는 노티파이 함수
void UAnimalAnim::AnimNotify_AttackEnd()
{
	AAnimal* pOwner = Cast<AAnimal>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->AttackEnd();
		pOwner->EnableAttackCollision(false);
		pOwner->SetEndOverlapEnable(true);
	}
}

void UAnimalAnim::AnimNotify_HitEnd()
{
	AnimType = (uint8)EAnimalAnim::Idle;
}

void UAnimalAnim::AnimNotify_DeathEnd()
{
	AAnimal* pOwner = Cast<AAnimal>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->Death();

}

