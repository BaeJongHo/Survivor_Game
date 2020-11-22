// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Run.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UBTTask_Run : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Run();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds);

};
