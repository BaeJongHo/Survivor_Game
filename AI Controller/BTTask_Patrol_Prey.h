// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Patrol_Prey.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UBTTask_Patrol_Prey : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Patrol_Prey();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds);
	
};
