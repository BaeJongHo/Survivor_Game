// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDetect_Prey.h"
#include "PreyAIController.h"
#include "PreyAnimal.h"

UBTService_PlayerDetect_Prey::UBTService_PlayerDetect_Prey()
{
	NodeName = TEXT("PlayerDetect_Prey");
	Interval = 0.5f;
}

// 매초마다 실행되는 함수
void UBTService_PlayerDetect_Prey::TickNode(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APreyAIController* pController = Cast<APreyAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(pController))
		return;

	APreyAnimal* pPreyAnimal = Cast<APreyAnimal>(pController->GetPawn());

	if (!IsValid(pPreyAnimal))
		return;

	FCollisionQueryParams params(NAME_None, false, pPreyAnimal);

	// 생성되는 구 모형과 겹치는 채널을 resultArray에 담는 함수입니다.
	TArray<FOverlapResult> resultArray;
	bool bOverlap = GetWorld()->OverlapMultiByChannel(resultArray, pPreyAnimal->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(pPreyAnimal->GetTraceRange()), params);

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

