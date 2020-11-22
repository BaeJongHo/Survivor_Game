// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "AIController.h"
#include "PreyAIController.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API APreyAIController : public AAIController
{
	GENERATED_BODY()

public:
	APreyAIController();

protected:
	UBehaviorTree* m_pBTAsset;
	UBlackboardData* m_pBBAsset;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	void SetTarget(UObject* pTarget);
	ACharacter* GetTarget() const;
	
};
