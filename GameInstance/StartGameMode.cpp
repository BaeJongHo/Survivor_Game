// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "StartLevelWidget.h"

AStartGameMode::AStartGameMode()
{
	static ConstructorHelpers::FClassFinder<UStartLevelWidget> StartWidgetClass(TEXT("WidgetBlueprint'/Game/UI/UI_StartLevel.UI_StartLevel_C'"));

	if (StartWidgetClass.Succeeded())
		StartLevelWidgetClass = StartWidgetClass.Class;
}

// ���α׷��� �����ϸ� ȣ��Ǵ� �Լ�
void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StartLevelWidgetClass))
	{
		// ������ �����Ѵ�
		StartLevelWidget = Cast<UStartLevelWidget>(CreateWidget(GetWorld(), StartLevelWidgetClass));

		if (IsValid(StartLevelWidget))
		{
			// ������ ����Ʈ�� �߰��Ѵ�
			StartLevelWidget->AddToViewport();
		}
	}
}

