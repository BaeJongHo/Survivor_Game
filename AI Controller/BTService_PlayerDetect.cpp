// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDetect.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTService_PlayerDetect::UBTService_PlayerDetect()
{
	NodeName = TEXT("PlayerDetect");
	Interval = 0.5f;
}

// ���ʸ��� ����Ǵ� �Լ�
void UBTService_PlayerDetect::TickNode(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APredatorAIController* pController = Cast<APredatorAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return;

	APredatorAnimal* pPredatorAnimal = Cast<APredatorAnimal>(pController->GetPawn());

	if (!IsValid(pPredatorAnimal))
		return;

	FCollisionQueryParams params(NAME_None, false, pPredatorAnimal);

	// �����Ǵ� �� ������ ��ġ�� ä���� resultArray�� ��� �Լ��Դϴ�.
	TArray<FOverlapResult> resultArray;
	bool bOverlap = GetWorld()->OverlapMultiByChannel(resultArray, pPredatorAnimal->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(pPredatorAnimal->GetTraceRange()), params);

	// ������ Ÿ���� �����ϸ� Ÿ���� �����մϴ�
	if (bOverlap)
	{
		pController->SetTarget(resultArray[0].GetActor());
	}
	else
	{
		pController->SetTarget(nullptr);
	}
}