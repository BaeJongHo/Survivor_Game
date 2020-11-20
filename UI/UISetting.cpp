// Fill out your copyright notice in the Description page of Project Settings.


#include "UISetting.h"
#include "Components/Button.h"

// 위젯 클래스의 생성자
void UUISetting::NativeConstruct()
{
	Super::NativeConstruct();

	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
	PlayButton = Cast<UButton>(GetWidgetFromName(TEXT("PlayButton")));
	SaveButton = Cast<UButton>(GetWidgetFromName(TEXT("SaveButton")));
	EndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
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

// Play 버튼 클릭시 실행될 함수
void UUISetting::PlayButtonCallback()
{
	PrintViewport(2.f, FColor::Magenta, "Play Success");

}

// Save 버튼 클릭시 실행될 함수
void UUISetting::SaveButtonCallback()
{
	PrintViewport(2.f, FColor::Magenta, "Save Success");

}

// End 버튼 클릭시 실행될 함수
void UUISetting::EndButtonCallback()
{
	PrintViewport(2.f, FColor::Magenta, "Setting Success");
	// 게임 종료 함수
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

