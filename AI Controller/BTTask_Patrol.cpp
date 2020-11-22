// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	// ������ ��ġ�� Patrol Point�� ��ġ�� ���´�
	FVector vPredatorAnimalLoc = pPredatorAnimal->GetActorLocation();
	FVector vPatrolPointLoc = pPredatorAnimal->GetPatrolPoint()->GetActorLocation();
	vPatrolPointLoc.Z = vPredatorAnimalLoc.Z;

	// ���͸� Patrol Point ��ġ�� �̵���Ų��
	pController->MoveToActor(pPredatorAnimal->GetPatrolPoint(), -1.f, false, true);
	pPredatorAnimal->SetAnimType(EAnimalAnim::Run);

	vPredatorAnimalLoc.Z = 0.f;
	vPatrolPointLoc.Z = 0.f;

	// �� ������ �Ÿ��� ���Ѵ�
	float fDist = FVector::Distance(vPredatorAnimalLoc, vPatrolPointLoc);

	// ���� ��ü�� ��ġ�� �����ߴ��� �Ǵ��Ѵ�
	if (fDist <= 10.f)
	{
		// ������ �̵��� ���߰� Patrol Point�� ���� ������ �����Ѵ�
		pPredatorAnimal->SetAnimType(EAnimalAnim::Idle);
		pController->StopMovement();
		pPredatorAnimal->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


