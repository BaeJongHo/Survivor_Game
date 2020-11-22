// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_PatrolEnable.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTDecorator_PatrolEnable::UBTDecorator_PatrolEnable()
{
	NodeName = TEXT("PatrolEnable");
}

bool UBTDecorator_PatrolEnable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return false;

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	if (!IsValid(pPredatorAnimal))
		return false;

	if (pPredatorAnimal->GetPatrolPointCount() < 2)
		return false;

	return true;
}



