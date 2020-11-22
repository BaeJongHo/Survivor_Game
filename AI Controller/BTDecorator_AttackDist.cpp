// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_AttackDist.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTDecorator_AttackDist::UBTDecorator_AttackDist()
{
	NodeName = TEXT("AttackDistance");
}

bool UBTDecorator_AttackDist::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return false;

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	if (!IsValid(pPredatorAnimal))
		return false;

	if (pPredatorAnimal->GetAttack())
	{
		pController->StopMovement();
		return true;
	}

	ACharacter* pTarget = pController->GetTarget();

	if (!IsValid(pTarget))
		return false;

	// Ÿ�ٰ��� �Ÿ��� ���Ѵ�
	// ���� ��ġ���� �̿��ϸ� ������ �߻��� �� �����Ƿ�
	// �� ��ġ�� Z���� 0���� �� �Ŀ� �Ÿ��� üũ�Ѵ�
	FVector vAILoc = pPredatorAnimal->GetActorLocation();
	FVector vTargetLoc = pTarget->GetActorLocation();

	vAILoc.Z = 0.f;
	vTargetLoc.Z = 0.f;

	float fDist = FVector::Distance(vAILoc, vTargetLoc);

	if (fDist <= pPredatorAnimal->GetAttackRange())
	{
		//pController->StopMovement();
		return true;
	}

	return false;
}

