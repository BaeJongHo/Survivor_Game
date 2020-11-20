// Fill out your copyright notice in the Description page of Project Settings.

#include "UIAttackState.h"
#include "Components/Image.h"

void UUIAttackState::NativeConstruct()
{
	Super::NativeConstruct();

	IconImage = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
}

void UUIAttackState::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UUIAttackState::SetIconTexture(const FString& strPath)
{
	UTexture2D* IconTex = LoadObject<UTexture2D>(nullptr, *strPath);

	IconImage->SetBrushFromTexture(IconTex);
}

void UUIAttackState::SetIconTexture(UTexture2D* pTex)
{
	IconImage->SetBrushFromTexture(pTex);
}
