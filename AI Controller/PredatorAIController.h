// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "AIController.h"
#include "PredatorAIController.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API APredatorAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APredatorAIController();

protected:
	UBehaviorTree* m_pBTAsset;
	UBlackboardData* m_pBBAsset;
	ACharacter* m_pTarget;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	void SetTarget(UObject* pTarget);
	ACharacter* GetTarget() const;
};
