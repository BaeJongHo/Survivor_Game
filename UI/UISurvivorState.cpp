// Fill out your copyright notice in the Description page of Project Settings.

#include "UISurvivorState.h"

void UUISurvivorState::NativeConstruct()
{
	Super::NativeConstruct();

	SurvivorBar = Cast<UUISurvivorBar>(GetWidgetFromName(TEXT("UI_SurvivorBar")));
	Inventory = Cast<UInventory>(GetWidgetFromName(TEXT("UI_Inventory")));
	Recipe = Cast<URecipe>(GetWidgetFromName(TEXT("UI_Recipe")));
	Setting = Cast<UUISetting>(GetWidgetFromName(TEXT("UI_Setting")));
	ArrowState = Cast<UUIArrowState>(GetWidgetFromName(TEXT("UI_ArrowState")));
	AttackState = Cast<UUIAttackState>(GetWidgetFromName(TEXT("UI_AttackState")));
}

void UUISurvivorState::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}
