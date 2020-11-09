// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "StartLevelWidget.h"

AStartGameMode::AStartGameMode()
{
	static ConstructorHelpers::FClassFinder<UStartLevelWidget> StartWidgetClass(TEXT("WidgetBlueprint'/Game/UI/UI_StartLevel.UI_StartLevel_C'"));

	if (StartWidgetClass.Succeeded())
		StartLevelWidgetClass = StartWidgetClass.Class;
}

// 프로그램이 시작하면 호출되는 함수
void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StartLevelWidgetClass))
	{
		// 위젯을 생성한다
		StartLevelWidget = Cast<UStartLevelWidget>(CreateWidget(GetWorld(), StartLevelWidgetClass));

		if (IsValid(StartLevelWidget))
		{
			// 위젯을 뷰포트에 추가한다
			StartLevelWidget->AddToViewport();
		}
	}
}

