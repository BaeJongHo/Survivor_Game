// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDetect.h"
#include "PredatorAIController.h"
#include "PredatorAnimal.h"

UBTService_PlayerDetect::UBTService_PlayerDetect()
{
	NodeName = TEXT("PlayerDetect");
	Interval = 0.5f;
}

// 매초마다 실행되는 함수
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

	// 생성되는 구 모형과 겹치는 채널을 resultArray에 담는 함수입니다.
	TArray<FOverlapResult> resultArray;
	bool bOverlap = GetWorld()->OverlapMultiByChannel(resultArray, pPredatorAnimal->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(pPredatorAnimal->GetTraceRange()), params);

	// 겹쳐진 타겟이 존재하면 타겟을 세팅합니다
	if (bOverlap)
	{
		pController->SetTarget(resultArray[0].GetActor());
	}
	else
	{
		pController->SetTarget(nullptr);
	}
}