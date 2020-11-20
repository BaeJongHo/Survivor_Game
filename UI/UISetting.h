// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "UISetting.generated.h"

UCLASS()
class SURVIVAL_IN_AFRICA_API UUISetting : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* PlayButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* SaveButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* EndButton;

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
public:
	void VisibleSetting(ESlateVisibility eVisibility);

private:
	// ��ư�� ������ ��, ȣ��� ��������Ʈ�� ����� �Լ�
	UFUNCTION(BlueprintCallable)
	void PlayButtonCallback();

	UFUNCTION(BlueprintCallable)
	void SaveButtonCallback();

	UFUNCTION(BlueprintCallable)
	void EndButtonCallback();
};
