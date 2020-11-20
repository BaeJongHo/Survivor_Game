// Fill out your copyright notice in the Description page of Project Settings.

#include "UISurvivorBar.h"
#include "Components/ProgressBar.h"

void UUISurvivorBar::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	MoistureBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MoistureBar")));
}

void UUISurvivorBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

// HP 게이지를 세팅하는 함수
void UUISurvivorBar::SetHP(float fPercent)
{
	if (IsValid(HPBar))
		HPBar->SetPercent(fPercent);
}

// 수분 게이지를 세팅하는 함수
void UUISurvivorBar::SetMoisture(float fPercent)
{
	if (IsValid(MoistureBar))
		MoistureBar->SetPercent(fPercent);
}


