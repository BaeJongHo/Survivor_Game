// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "StartPlayerController.h"
#include "StartLevelWidget.h"

AStartGameMode::AStartGameMode()
{
	static ConstructorHelpers::FClassFinder<UStartLevelWidget> StartWidgetClass(TEXT("WidgetBlueprint'/Game/UI/UI_StartLevel.UI_StartLevel_C'"));

	if (StartWidgetClass.Succeeded())
		StartLevelWidgetClass = StartWidgetClass.Class;

	static ConstructorHelpers::FClassFinder<AStartPlayerController>	ControllerClass(TEXT("Blueprint'/Game/Player/BPStartPlayerController.BPStartPlayerController_C'"));

	if (ControllerClass.Succeeded())
		PlayerControllerClass = ControllerClass.Class;

	static ConstructorHelpers::FObjectFinder<USoundCue> StartMusicAsset(TEXT("SoundCue'/Game/FantasyOrchestral/cues/StartGameSound.StartGameSound'"));

	if (StartMusicAsset.Succeeded())
		StartMusicCue = StartMusicAsset.Object;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
}

// ���α׷��� �����ϸ� ȣ��Ǵ� �Լ�
void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent->SetSound(StartMusicCue);
	AudioComponent->Play();

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
