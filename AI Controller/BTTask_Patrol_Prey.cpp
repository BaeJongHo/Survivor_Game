// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol_Prey.h"
#include "PreyAIController.h"
#include "PreyAnimal.h"

UBTTask_Patrol_Prey::UBTTask_Patrol_Prey()
{
	NodeName = TEXT("Patrol_Prey");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Patrol_Prey::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol_Prey::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APreyAIController* pController = Cast<APreyAIController>(OwnerComp.GetAIOwner());

	APreyAnimal* pPreyAnimal = Cast<APreyAnimal>(pController->GetPawn());

	// 몬스터의 위치와 Patrol Point의 위치를 얻어온다
	FVector vPreyAnimalLoc = pPreyAnimal->GetActorLocation();
	FVector vPatrolPointLoc = pPreyAnimal->GetPatrolPoint()->GetActorLocation();
	vPreyAnimalLoc.Z = vPatrolPointLoc.Z;

	// 몬스터를 Patrol Point 위치로 이동시킨다
	pController->MoveToActor(pPreyAnimal->GetPatrolPoint(), -1.f, false, true);
	pPreyAnimal->SetAnimType(EAnimalAnim::Run);

	vPreyAnimalLoc.Z = 0.f;
	vPatrolPointLoc.Z = 0.f;

	// 둘 사이의 거리를 구한다
	float fDist = FVector::Distance(vPreyAnimalLoc, vPatrolPointLoc);

	// 몬스터 객체가 위치에 도착했는지 판단한다
	if (fDist <= 5.f)
	{
		// 몬스터의 이동을 멈추고 Patrol Point를 다음 것으로 설정한다
		pPreyAnimal->SetAnimType(EAnimalAnim::Idle);
		pController->StopMovement();
		pPreyAnimal->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

