// Fill out your copyright notice in the Description page of Project Settings.


#include "UIArrowState.h"
#include "Components/TextBlock.h"

void UUIArrowState::NativeConstruct()
{
	Super::NativeConstruct();

	ArrowNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArrowNum")));
	ArrowNumMax = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArrowNumMax")));
}

void UUIArrowState::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

// ���� ȭ�� ������ �����ϴ� �Լ�
void UUIArrowState::SetArrowNum(int32 ArrowCount)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), ArrowCount);

	ArrowNum->SetText(FText::FromString(strText));
}

// �ִ� ȭ�� ������ �����ϴ� �Լ�
void UUIArrowState::SetArrowNumMax(int32 ArrowCountMax)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), ArrowCountMax);

	ArrowNumMax->SetText(FText::FromString(strText));
}

