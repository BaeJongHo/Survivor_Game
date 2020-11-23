// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelWidget.h"
#include "Components/Button.h"
#include "MainGameInstance.h"
#include "SaveSurvivorState.h"
#include "UICheckNewGame.h"
#include "UICheckContinueGame.h"

// 위젯 클래스의 생성자
void UStartLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
	NewGameButton = Cast<UButton>(GetWidgetFromName(TEXT("NewGameButton")));
	ContinueButton = Cast<UButton>(GetWidgetFromName(TEXT("ContinueButton")));
	EndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));
	CheckNewGame = Cast<UUICheckNewGame>(GetWidgetFromName(TEXT("UI_CheckNewGame")));
	CheckContinueGame = Cast<UUICheckContinueGame>(GetWidgetFromName(TEXT("UI_CheckContinueGame")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	NewGameButton->OnClicked.AddDynamic(this, &UStartLevelWidget::NewGameButtonCallback);
	ContinueButton->OnClicked.AddDynamic(this, &UStartLevelWidget::ContinueButtonCallback);
	EndButton->OnClicked.AddDynamic(this, &UStartLevelWidget::EndButtonCallback);
}

void UStartLevelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

// New Game 버튼 클릭시 실행될 함수
void UStartLevelWidget::NewGameButtonCallback()
{
	USaveSurvivorState* LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::CreateSaveGameObject(USaveSurvivorState::StaticClass()));
	LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	// sav 파일이 있을 경우
	if (IsValid(LoadGameInstance))
	{
		// 확인 문구 UI를 띄워준다
		CheckNewGame->VisibleCheck(ESlateVisibility::Visible);
	}

	// sav 파일이 없을 경우 바로 시작
	else
	{
		UMainGameInstance* GameInst = GetGameInstance<UMainGameInstance>();
		GameInst->SetContinueGame(false);

		// 레벨을 바꿔주는 함수
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Africa"));
	}
}

// Continue 버튼 클릭시 실행될 함수
void UStartLevelWidget::ContinueButtonCallback()
{
	USaveSurvivorState* LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::CreateSaveGameObject(USaveSurvivorState::StaticClass()));
	LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	// sav 파일이 없을 경우
	if (!IsValid(LoadGameInstance))
	{
		CheckContinueGame->VisibleCheck(ESlateVisibility::Visible);
	}

	// sav 파일이 있을 경우 바로 시작
	else
	{
		UMainGameInstance* GameInst = GetGameInstance<UMainGameInstance>();
		GameInst->SetContinueGame(true);

		// 레벨을 바꿔주는 함수
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Africa"));
	}
}

// End 버튼 클릭시 실행될 함수
void UStartLevelWidget::EndButtonCallback()
{
	// 게임 종료 함수
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController() , EQuitPreference::Quit, true);
}
