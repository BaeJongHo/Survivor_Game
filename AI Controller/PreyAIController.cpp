// Fill out your copyright notice in the Description page of Project Settings.


#include "PreyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "PreyAnimal.h"

APreyAIController::APreyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAsset(TEXT("BehaviorTree'/Game/Animal/BTPrey.BTPrey'"));

	if (BTAsset.Succeeded())
		m_pBTAsset = BTAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsset(TEXT("BlackboardData'/Game/Animal/BBPrey.BBPrey'"));

	if (BBAsset.Succeeded())
		m_pBBAsset = BBAsset.Object;
}

void APreyAIController::OnPossess(APawn* InPawn)
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

void APreyAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void APreyAIController::SetTarget(UObject* pTarget)
{
	Blackboard->SetValueAsObject(TEXT("Target"), pTarget);
}

ACharacter* APreyAIController::GetTarget() const
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(TEXT("Target")));
}


