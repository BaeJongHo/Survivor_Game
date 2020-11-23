// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelWidget.h"
#include "Components/Button.h"
#include "MainGameInstance.h"
#include "SaveSurvivorState.h"
#include "UICheckNewGame.h"
#include "UICheckContinueGame.h"

// ���� Ŭ������ ������
void UStartLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ���� �������Ʈ�� ��ư�� �̸��� ���� �����´�
	NewGameButton = Cast<UButton>(GetWidgetFromName(TEXT("NewGameButton")));
	ContinueButton = Cast<UButton>(GetWidgetFromName(TEXT("ContinueButton")));
	EndButton = Cast<UButton>(GetWidgetFromName(TEXT("EndButton")));
	CheckNewGame = Cast<UUICheckNewGame>(GetWidgetFromName(TEXT("UI_CheckNewGame")));
	CheckContinueGame = Cast<UUICheckContinueGame>(GetWidgetFromName(TEXT("UI_CheckContinueGame")));

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	NewGameButton->OnClicked.AddDynamic(this, &UStartLevelWidget::NewGameButtonCallback);
	ContinueButton->OnClicked.AddDynamic(this, &UStartLevelWidget::ContinueButtonCallback);
	EndButton->OnClicked.AddDynamic(this, &UStartLevelWidget::EndButtonCallback);
}

void UStartLevelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

// New Game ��ư Ŭ���� ����� �Լ�
void UStartLevelWidget::NewGameButtonCallback()
{
	USaveSurvivorState* LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::CreateSaveGameObject(USaveSurvivorState::StaticClass()));
	LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	// sav ������ ���� ���
	if (IsValid(LoadGameInstance))
	{
		// Ȯ�� ���� UI�� ����ش�
		CheckNewGame->VisibleCheck(ESlateVisibility::Visible);
	}

	// sav ������ ���� ��� �ٷ� ����
	else
	{
		UMainGameInstance* GameInst = GetGameInstance<UMainGameInstance>();
		GameInst->SetContinueGame(false);

		// ������ �ٲ��ִ� �Լ�
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Africa"));
	}
}

// Continue ��ư Ŭ���� ����� �Լ�
void UStartLevelWidget::ContinueButtonCallback()
{
	USaveSurvivorState* LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::CreateSaveGameObject(USaveSurvivorState::StaticClass()));
	LoadGameInstance = Cast<USaveSurvivorState>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	// sav ������ ���� ���
	if (!IsValid(LoadGameInstance))
	{
		CheckContinueGame->VisibleCheck(ESlateVisibility::Visible);
	}

	// sav ������ ���� ��� �ٷ� ����
	else
	{
		UMainGameInstance* GameInst = GetGameInstance<UMainGameInstance>();
		GameInst->SetContinueGame(true);

		// ������ �ٲ��ִ� �Լ�
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Africa"));
	}
}

// End ��ư Ŭ���� ����� �Լ�
void UStartLevelWidget::EndButtonCallback()
{
	// ���� ���� �Լ�
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController() , EQuitPreference::Quit, true);
}
