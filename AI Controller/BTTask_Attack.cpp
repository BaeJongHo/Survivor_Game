// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
	bAttack = false;
}

// Task의 상태를 반환하는 함수
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	// 컨트롤러가 타당하지 않다면 실패 처리
	if (!IsValid(pController))
		return EBTNodeResult::Failed;
	
	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	// 몬스터가 타당하지 않다면 실패 처리
	if (!IsValid(pPredatorAnimal))
		return EBTNodeResult::Failed;

	// 공격 사거리에 들어왔을때 AttackEnd 함수를 델리게이트로 등록한다
	pPredatorAnimal->AddAttackEndDelegate<UBTTask_Attack>(this, &UBTTask_Attack::AttackEnd);

	// 몬스터가 살아있을 때 공격을 시작한다
	pPredatorAnimal->SetAnimType(EAnimalAnim::Attack);

	bAttack = true;

	pPredatorAnimal->Attack(); // 몬스터 공격 상태 등록

	return EBTNodeResult::InProgress;
}

// 매초마다 호출되는 함수
void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	ACharacter* pTarget = pController->GetTarget();

	// 타겟이 공격 사거리에서 벗어나면 Task 실패 처리한다
	/*
	if (!pTarget)
	{
		//pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	*/

	// 타겟을 바라보도록 회전시킨다
	FVector vDir = pTarget->GetActorLocation() - pPredatorAnimal->GetActorLocation();
	vDir.Normalize(); // 방향 정보만 필요하기 때문에 Normalize를 적용한다

	// 계산한 방향으로 몬스터를 강제 Yaw 회전시킨다
	pPredatorAnimal->SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

	// 공격이 끝났을 경우 종료시킨다
	if (!bAttack)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Attack::AttackEnd()
{
	bAttack = false;
}
