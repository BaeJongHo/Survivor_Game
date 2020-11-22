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

// ���ʸ��� ����Ǵ� �Լ�
void UBTTask_Run::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APreyAIController* pController = Cast<APreyAIController>(OwnerComp.GetAIOwner());

	APreyAnimal* pPreyAnimal = Cast<APreyAnimal>(pController->GetPawn());

	ACharacter* pTarget = pController->GetTarget();

	// Ÿ���� �������� �ʴ´ٸ� ���߰� Task�� Failed ó���Ѵ�
	if (!pTarget)
	{
		pPreyAnimal->SetAnimType(EAnimalAnim::Idle);
		pController->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	// Ÿ�ٰ� �ݴ� ������ �ٶ󺸵��� ȸ����Ų��
	FVector vDir = pTarget->GetActorLocation() - pPreyAnimal->GetActorLocation();
	vDir.Normalize(); // ���� ������ �ʿ��ϱ� ������ Normalize�� �����Ѵ�
	vDir = -vDir; // �ݴ� ���� ���͸� ���Ѵ�

	// ����� �������� ���͸� ���� Yaw ȸ����Ų��
	pPreyAnimal->SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

	// ������ ��ġ�� Ÿ���� ��ġ�� ���´�
	FVector vPreyAnimalLoc = pPreyAnimal->GetActorLocation();
	FVector vTargetLoc = pTarget->GetActorLocation();

	// Ÿ�� ��ġ���� ������ ��ġ�� ��Ī�ϴ� ���� ã�´�
	FVector vGoalArea;
	vGoalArea.X = vPreyAnimalLoc.X - (vTargetLoc.X - vPreyAnimalLoc.X);
	vGoalArea.Y = vPreyAnimalLoc.Y - (vTargetLoc.Y - vPreyAnimalLoc.Y);
	vGoalArea.Z = vPreyAnimalLoc.Z;

	// ��Ī�ϴ� ������ �̵���Ų��
	pController->MoveToLocation(vGoalArea);
	pPreyAnimal->SetAnimType(EAnimalAnim::Run);
}

