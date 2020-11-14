// Fill out your copyright notice in the Description page of Project Settings.


#include "PredatorAnimal.h"
#include "PredatorAIController.h"

APredatorAnimal::APredatorAnimal()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void APredatorAnimal::BeginPlay()
{
	Super::BeginPlay();

}

void APredatorAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Actor Ŭ������ �����ϴ� �𸮾��� �������ִ� ������ �Լ�
float APredatorAnimal::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
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

		APredatorAIController* pPredatorController = GetController<APredatorAIController>();

		if (IsValid(pPredatorController))
		{
			UBehaviorTreeComponent* BT = Cast<UBehaviorTreeComponent>(pPredatorController->GetBrainComponent());

			if (IsValid(BT))
				BT->StopTree();
		}
	}
	return fDamage;
}
