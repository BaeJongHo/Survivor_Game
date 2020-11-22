// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PlayerDetect_Prey.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UBTService_PlayerDetect_Prey : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_PlayerDetect_Prey();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
