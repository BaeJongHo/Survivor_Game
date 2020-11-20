// Fill out your copyright notice in the Description page of Project Settings.

#include "UIRecipeDescription.h"
#include "Components/TextBlock.h"

// ���� Ŭ������ ������
void UUIRecipeDescription::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� �������Ʈ�� ��ư�� �̸��� ���� �����´�
	DescriptionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));

}

void UUIRecipeDescription::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UUIRecipeDescription::SetItemDescription(const FString& strDescription)
{
	DescriptionText->SetText(FText::FromString(strDescription));
}


