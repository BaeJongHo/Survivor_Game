// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameInstance.h"

UMainGameInstance::UMainGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnimalInfoAsset(TEXT("DataTable'/Game/Animal/AnimalInfoTable.AnimalInfoTable'"));

	if (AnimalInfoAsset.Succeeded())
		AnimalInfoTable = AnimalInfoAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> SurvivorInfoAsset(TEXT("DataTable'/Game/Player/SurvivorInfoTable.SurvivorInfoTable'"));

	if (SurvivorInfoAsset.Succeeded())
		SurvivorInfoTable = SurvivorInfoAsset.Object;
}

UMainGameInstance::~UMainGameInstance()
{

}

void UMainGameInstance::Init()
{
	Super::Init();
}

const FAnimalInfo* UMainGameInstance::FindAnimalInfo(const FName& key) const
{
	if (!IsValid(AnimalInfoTable))
		return nullptr;

	return AnimalInfoTable->FindRow<FAnimalInfo>(key, TEXT(""));
}

const FSurvivorInfo* UMainGameInstance::FindSurvivorInfo(const FName& key) const
{
	if (!IsValid(SurvivorInfoTable))
		return nullptr;

	return SurvivorInfoTable->FindRow<FSurvivorInfo>(key, TEXT(""));
}