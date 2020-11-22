// Fill out your copyright notice in the Description page of Project Settings.


#include "PredatorAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "PredatorAnimal.h"

APredatorAIController::APredatorAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("BehaviorTree'/Game/Animal/BTPredator.BTPredator'"));

	if (BTAsset.Succeeded())
		m_pBTAsset = BTAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsset(TEXT("BlackboardData'/Game/Animal/BBPredator.BBPredator'"));

	if (BBAsset.Succeeded())
		m_pBBAsset = BBAsset.Object;

	m_pTarget = nullptr;
}

void APredatorAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 사용하려는 블랙보드를 지정한다
	if (UseBlackboard(m_pBBAsset, Blackboard))
	{
		// 행동트리를 지정하고 동작하게 한다
		if (!RunBehaviorTree(m_pBTAsset))
		{
		}
	}
}

void APredatorAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

// 타겟 설정
void APredatorAIController::SetTarget(UObject* pTarget)
{
	Blackboard->SetValueAsObject(TEXT("Target"), pTarget);

	if (pTarget)
		m_pTarget = Cast<ACharacter>(pTarget);
	else
		m_pTarget = nullptr;
}

ACharacter* APredatorAIController::GetTarget() const
{
	return m_pTarget;
}

