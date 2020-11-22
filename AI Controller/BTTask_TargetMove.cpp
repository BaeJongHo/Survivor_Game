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

	// Ÿ���� �������� �ʴ´ٸ� ���߰� Task�� Failed ó���Ѵ�
	if (!pTarget)
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// ���Ͱ� ����ִٸ� �̵��� �Ѵ�
	// �̵��� �����ϴ� �Լ�
	UAIBlueprintHelperLibrary::SimpleMoveToActor(pController, pTarget);
	pPredatorAnimal->SetAnimType(EAnimalAnim::Run);

	// ���Ϳ� Ÿ�� ������ �Ÿ��� ���Ѵ�
	FVector vAILoc = pPredatorAnimal->GetActorLocation();
	FVector vTargetLoc = pTarget->GetActorLocation();

	vAILoc.Z = 0.f;
	vTargetLoc.Z = 0.f;

	float fDist = FVector::Distance(vAILoc, vTargetLoc);

	// �Ÿ��� ���� ��Ÿ� ���ϰ� �ȴٸ� ���߰� Task�� ���¸� �������� ó���Ѵ�
	if (fDist <= pPredatorAnimal->GetAttackRange())
	{
		pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}


