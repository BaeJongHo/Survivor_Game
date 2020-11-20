// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UISurvivorBar.h"
#include "Inventory.h"
#include "Recipe.h"
#include "UISetting.h"
#include "UIArrowState.h"
#include "UIAttackState.h"
#include "Blueprint/UserWidget.h"
#include "UISurvivorState.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UUISurvivorState : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUISurvivorBar* SurvivorBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	URecipe* Recipe;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUISetting* Setting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUIArrowState* ArrowState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUIAttackState* AttackState;
	
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UUISurvivorBar* GetSurvivorBar() const
	{
		return SurvivorBar;
	}

	UInventory* GetInventory() const
	{
		return Inventory;
	}

	URecipe* GetRecipe() const
	{
		return Recipe;
	}

	UUISetting* GetSetting() const
	{
		return Setting;
	}

	UUIArrowState* GetArrowState() const
	{
		return ArrowState;
	}

	UUIAttackState* GetAttackState() const
	{
		return AttackState;
	}
};
