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

// Actor 클래스에 존재하는 언리얼이 제공해주는 데미지 함수
float APreyAnimal::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 현재 체력에서 fDamage의 크기만큼 감소시킨다
	AnimalState.iHP -= (int32)(DamageAmount - AnimalState.fArmor);

	// 만약 HP가 0보다 작아진다면 Death 모션 적용
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


