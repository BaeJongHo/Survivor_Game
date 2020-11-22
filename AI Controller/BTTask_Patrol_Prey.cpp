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

	// ������ ��ġ�� Patrol Point�� ��ġ�� ���´�
	FVector vPreyAnimalLoc = pPreyAnimal->GetActorLocation();
	FVector vPatrolPointLoc = pPreyAnimal->GetPatrolPoint()->GetActorLocation();
	vPreyAnimalLoc.Z = vPatrolPointLoc.Z;

	// ���͸� Patrol Point ��ġ�� �̵���Ų��
	pController->MoveToActor(pPreyAnimal->GetPatrolPoint(), -1.f, false, true);
	pPreyAnimal->SetAnimType(EAnimalAnim::Run);

	vPreyAnimalLoc.Z = 0.f;
	vPatrolPointLoc.Z = 0.f;

	// �� ������ �Ÿ��� ���Ѵ�
	float fDist = FVector::Distance(vPreyAnimalLoc, vPatrolPointLoc);

	// ���� ��ü�� ��ġ�� �����ߴ��� �Ǵ��Ѵ�
	if (fDist <= 5.f)
	{
		// ������ �̵��� ���߰� Patrol Point�� ���� ������ �����Ѵ�
		pPreyAnimal->SetAnimType(EAnimalAnim::Idle);
		pController->StopMovement();
		pPreyAnimal->NextPatrolPoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

