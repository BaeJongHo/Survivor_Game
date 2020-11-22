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

// Task�� ���¸� ��ȯ�ϴ� �Լ�
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	// ��Ʈ�ѷ��� Ÿ������ �ʴٸ� ���� ó��
	if (!IsValid(pController))
		return EBTNodeResult::Failed;
	
	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	// ���Ͱ� Ÿ������ �ʴٸ� ���� ó��
	if (!IsValid(pPredatorAnimal))
		return EBTNodeResult::Failed;

	// ���� ��Ÿ��� �������� AttackEnd �Լ��� ��������Ʈ�� ����Ѵ�
	pPredatorAnimal->AddAttackEndDelegate<UBTTask_Attack>(this, &UBTTask_Attack::AttackEnd);

	// ���Ͱ� ������� �� ������ �����Ѵ�
	pPredatorAnimal->SetAnimType(EAnimalAnim::Attack);

	bAttack = true;

	pPredatorAnimal->Attack(); // ���� ���� ���� ���

	return EBTNodeResult::InProgress;
}

// ���ʸ��� ȣ��Ǵ� �Լ�
void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	ACharacter* pTarget = pController->GetTarget();

	// Ÿ���� ���� ��Ÿ����� ����� Task ���� ó���Ѵ�
	/*
	if (!pTarget)
	{
		//pController->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	*/

	// Ÿ���� �ٶ󺸵��� ȸ����Ų��
	FVector vDir = pTarget->GetActorLocation() - pPredatorAnimal->GetActorLocation();
	vDir.Normalize(); // ���� ������ �ʿ��ϱ� ������ Normalize�� �����Ѵ�

	// ����� �������� ���͸� ���� Yaw ȸ����Ų��
	pPredatorAnimal->SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

	// ������ ������ ��� �����Ų��
	if (!bAttack)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_Attack::AttackEnd()
{
	bAttack = false;
}
