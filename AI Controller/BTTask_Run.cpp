// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Run.h"
#include "PreyAIController.h"
#include "PreyAnimal.h"

UBTTask_Run::UBTTask_Run()
{
	NodeName = TEXT("Run");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Run::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APreyAIController* pController = Cast<APreyAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return EBTNodeResult::Failed;

	APreyAnimal* pPreyAnimal = Cast<APreyAnimal>(pController->GetPawn());

	if (!IsValid(pPreyAnimal))
		return EBTNodeResult::Failed;

	ACharacter* pTarget = pController->GetTarget();

	if (!IsValid(pTarget))
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

// 매초마다 실행되는 함수
void UBTTask_Run::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APreyAIController* pController = Cast<APreyAIController>(OwnerComp.GetAIOwner());

	APreyAnimal* pPreyAnimal = Cast<APreyAnimal>(pController->GetPawn());

	ACharacter* pTarget = pController->GetTarget();

	// 타겟이 존재하지 않는다면 멈추고 Task를 Failed 처리한다
	if (!pTarget)
	{
		pPreyAnimal->SetAnimType(EAnimalAnim::Idle);
		pController->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	// 타겟과 반대 방향을 바라보도록 회전시킨다
	FVector vDir = pTarget->GetActorLocation() - pPreyAnimal->GetActorLocation();
	vDir.Normalize(); // 방향 정보만 필요하기 때문에 Normalize를 적용한다
	vDir = -vDir; // 반대 방향 벡터를 구한다

	// 계산한 방향으로 몬스터를 강제 Yaw 회전시킨다
	pPreyAnimal->SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

	// 몬스터의 위치와 타겟의 위치를 얻어온다
	FVector vPreyAnimalLoc = pPreyAnimal->GetActorLocation();
	FVector vTargetLoc = pTarget->GetActorLocation();

	// 타겟 위치에서 몬스터의 위치와 대칭하는 점을 찾는다
	FVector vGoalArea;
	vGoalArea.X = vPreyAnimalLoc.X - (vTargetLoc.X - vPreyAnimalLoc.X);
	vGoalArea.Y = vPreyAnimalLoc.Y - (vTargetLoc.Y - vPreyAnimalLoc.Y);
	vGoalArea.Z = vPreyAnimalLoc.Z;

	// 대칭하는 점으로 이동시킨다
	pController->MoveToLocation(vGoalArea);
	pPreyAnimal->SetAnimType(EAnimalAnim::Run);
}

