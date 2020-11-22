// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_PatrolEnable_Prey.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UBTDecorator_PatrolEnable_Prey : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_PatrolEnable_Prey();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
};
