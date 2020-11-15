// Fill out your copyright notice in the Description page of Project Settings.


#include "PreyAnimal.h"
#include "PreyAIController.h"

APreyAnimal::APreyAnimal()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APreyAnimal::BeginPlay()
{
	Super::BeginPlay();

}

void APreyAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Actor Ŭ������ �����ϴ� �𸮾��� �������ִ� ������ �Լ�
float APreyAnimal::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// ���� ü�¿��� fDamage�� ũ�⸸ŭ ���ҽ�Ų��
	AnimalState.iHP -= (int32)(DamageAmount - AnimalState.fArmor);

	// ���� HP�� 0���� �۾����ٸ� Death ��� ����
	if (AnimalState.iHP <= 0)
	{
		AnimalState.iHP = 0;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (IsValid(AnimalAnim))
			AnimalAnim->SetAnimType(EAnimalAnim::Death);
		
		APreyAIController* pPreyController = GetController<APreyAIController>();

		if (IsValid(pPreyController))
		{
			UBehaviorTreeComponent* BT = Cast<UBehaviorTreeComponent>(pPreyController->GetBrainComponent());

			if (IsValid(BT))
				BT->StopTree();
		}
	}
	return fDamage;
}


