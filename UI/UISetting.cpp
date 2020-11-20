// Fill out your copyright notice in the Description page of Project Settings.


#include "UISetting.h"
#include "Components/Button.h"

// ���� Ŭ������ ������
void UUISetting::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� �������Ʈ�� ��ư�� �̸��� ���� �����´�
	PlayButton = Cast<UButton>(GetWidgetFromName(TEXT("PlayButton")));
	SaveButton = Cast<UButton>(GetWidgetFromName(TEXT("SaveButton")));
	EndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	PlayButton->OnClicked.AddDynamic(this, &UUISetting::PlayButtonCallback);
	SaveButton->OnClicked.AddDynamic(this, &UUISetting::SaveButtonCallback);
	EndButton->OnClicked.AddDynamic(this, &UUISetting::EndButtonCallback);
}

void UUISetting::VisibleSetting(ESlateVisibility eVisibility)
{
	this->SetVisibility(eVisibility);
}

void UUISetting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

// Play ��ư Ŭ���� ����� �Լ�
void UUISetting::PlayButtonCallback()
{
	PrintViewport(2.f, FColor::Magenta, "Play Success");

}

// Save ��ư Ŭ���� ����� �Լ�
void UUISetting::SaveButtonCallback()
{
	PrintViewport(2.f, FColor::Magenta, "Save Success");

}

// End ��ư Ŭ���� ����� �Լ�
void UUISetting::EndButtonCallback()
{
	PrintViewport(2.f, FColor::Magenta, "Setting Success");
	// ���� ���� �Լ�
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

