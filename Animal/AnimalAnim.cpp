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

	// �ڽ��� ������ �ִ� ���� ��ü�� �����´�
	AAnimal* pOwner = Cast<AAnimal>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		// ���� ��ü�� �������� ���´�
		UCharacterMovementComponent* pMovement = pOwner->GetCharacterMovement();

		if (IsValid(pMovement))
		{
			// ���Ͱ� �� ���� �ִ��� �Ǵ��Ѵ�
			if (pMovement->IsMovingOnGround())
			{
				// pMovement�� ����� ���� ���Ͱ� �����̰� �ִ��� �Ǵ��Ѵ�
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

// ������ ������ �� ȣ��Ǵ� ��Ƽ���� �Լ�
void UAnimalAnim::AnimNotify_AttackStart()
{
	AAnimal* pOwner = Cast<AAnimal>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->EnableAttackCollision(true);
}

// ������ ���� �� ȣ��Ǵ� ��Ƽ���� �Լ�
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

