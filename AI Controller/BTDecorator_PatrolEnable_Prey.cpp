// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_PatrolEnable_Prey.h"
#include "PreyAIController.h"
#include "PreyAnimal.h"

UBTDecorator_PatrolEnable_Prey::UBTDecorator_PatrolEnable_Prey()
{
	NodeName = TEXT("PatrolEnable_Prey");
}

bool UBTDecorator_PatrolEnable_Prey::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APreyAIController* pController = Cast<APreyAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return false;

	APreyAnimal* pPreyAnimal = Cast<APreyAnimal>(pController->GetPawn());

	if (!IsValid(pPreyAnimal))
		return false;

	if (pPreyAnimal->GetPatrolPointCount() < 2)
		return false;

	return true;
}

