// Fill out your copyright notice in the Description page of Project Settings.


#include "StartPlayerController.h"
#include "Blueprint/UserWidget.h"

AStartPlayerController::AStartPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> MouseAsset(TEXT("WidgetBlueprint'/Game/UI/UI_Mouse.UI_Mouse_C'"));

	if (MouseAsset.Succeeded())
		MouseWidgetClass = MouseAsset.Class;
}

void AStartPlayerController::BeginPlay()
{
	InputPitchScale = 0.f;
	InputYawScale = 0.f;
	InputRollScale = 0.f;

	FInputModeGameAndUI	inputMode;
	SetInputMode(inputMode);

	/*
	if (IsValid(MouseWidgetClass))
	{
		MouseWidget = CreateWidget(GetWorld(), MouseWidgetClass);

		if (IsValid(MouseWidget))
		{
			// 마우스 애셋 지정
			SetMouseCursorWidget(EMouseCursor::Default, MouseWidget);
		}
	}
	*/
}
