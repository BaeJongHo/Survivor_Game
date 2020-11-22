// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_TargetMove.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTTask_TargetMove::UBTTask_TargetMove()
{
	NodeName = TEXT("TargetMove");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_TargetMove::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return EBTNodeResult::Failed;

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	if (!IsValid(pPredatorAnimal))
		return EBTNodeResult::Failed;

	ACharacter* pTarget = pController->GetTarget();

	if (!IsValid(pTarget))
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_TargetMove::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	ACharacter* pTarget = pController->GetTarget();

	// 타겟이 존재하지 않는다면 멈추고 Task를 Failed 처리한다
	if (!pTarget)
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 몬스터가 살아있다면 이동을 한다
	// 이동을 지정하는 함수
	UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pTarget);
	pPredatorAnimal->SetAnimType(EAnimalAnim::Run);

	// 몬스터와 타겟 사이의 거리를 구한다
	FVector vAILoc = pPredatorAnimal->GetActorLocation();
	FVector vTargetLoc = pTarget->GetActorLocation();

	vAILoc.Z = 0.f;
	vTargetLoc.Z = 0.f;

	float fDist = FVector::Distance(vAILoc, vTargetLoc);

	// 거리가 공격 사거리 이하가 된다면 멈추고 Task의 상태를 성공으로 처리한다
	if (fDist <= pPredatorAnimal->GetAttackRange())
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}


