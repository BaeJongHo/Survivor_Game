// Fill out your copyright notice in the Description page of Project Settings.

#include "UIItemDescription.h"
#include "Components/TextBlock.h"

// ���� Ŭ������ ������
void UUIItemDescription::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� �������Ʈ�� ��ư�� �̸��� ���� �����´�
	DescriptionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));

}

void UUIItemDescription::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UUIItemDescription::SetItemDescription(const FString& strDescription)
{
	DescriptionText->SetText(FText::FromString(strDescription));
}
