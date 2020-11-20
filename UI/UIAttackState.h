// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "UIAttackState.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UUIAttackState : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* IconImage;

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
public:
	void SetIconTexture(const FString& strPath);
	void SetIconTexture(UTexture2D* pTex);
};
