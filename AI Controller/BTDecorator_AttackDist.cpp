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

	// 타겟과의 거리를 구한다
	// 실제 위치만을 이용하면 오차가 발생할 수 있으므로
	// 두 위치의 Z값을 0으로 둔 후에 거리를 체크한다
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

