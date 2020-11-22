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

	// 몬스터의 위치와 Patrol Point의 위치를 얻어온다
	FVector vPredatorAnimalLoc = pPredatorAnimal->GetActorLocation();
	FVector vPatrolPointLoc = pPredatorAnimal->GetPatrolPoint()->GetActorLocation();
	vPatrolPointLoc.Z = vPredatorAnimalLoc.Z;

	// 몬스터를 Patrol Point 위치로 이동시킨다
	pController->MoveToActor(pPredatorAnimal->GetPatrolPoint(), -1.f, false, true);
	pPredatorAnimal->SetAnimType(EAnimalAnim::Run);

	vPredatorAnimalLoc.Z = 0.f;
	vPatrolPointLoc.Z = 0.f;

	// 둘 사이의 거리를 구한다
	float fDist = FVector::Distance(vPredatorAnimalLoc, vPatrolPointLoc);

	// 몬스터 객체가 위치에 도착했는지 판단한다
	if (fDist <= 10.f)
	{
		// 몬스터의 이동을 멈추고 Patrol Point를 다음 것으로 설정한다
		pPredatorAnimal->SetAnimType(EAnimalAnim::Idle);
		pController->StopMovement();
		pPredatorAnimal->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


