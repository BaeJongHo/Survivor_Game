// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TargetMove.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UBTTask_TargetMove : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TargetMove();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds);

};
