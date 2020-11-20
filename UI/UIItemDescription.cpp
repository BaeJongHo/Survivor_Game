// Fill out your copyright notice in the Description page of Project Settings.

#include "UIItemDescription.h"
#include "Components/TextBlock.h"

// 위젯 클래스의 생성자
void UUIItemDescription::NativeConstruct()
{
	Super::NativeConstruct();

	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
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
