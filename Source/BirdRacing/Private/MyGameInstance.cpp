// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance()
{
	SelectedStageID = 0;
	TotalCoins = 0;
	FName_SelectStage = FName("SelectStage");
	FName_TitleScreen = FName("Title");
}

void UMyGameInstance::Init()
{
	Super::Init();
	InitializeDefaultData();
}

void UMyGameInstance::InitializeDefaultData()
{
	if (StageLevelNames.Num() == 0)
	{
		StageLevelNames.Add(1, FName("Stage_1"));
	}

	if (UnlockedStages.Num() == 0)
	{
		UnlockedStages.Add(true);
	}
}


void UMyGameInstance::LoadStageSelect()
{
	UGameplayStatics::OpenLevel(this, FName_SelectStage);
}

void UMyGameInstance::LoadStage(int32 StageID)
{
	if (!StageLevelNames.Contains(StageID))
	{
		UKismetSystemLibrary::PrintString(this, "Invalid Stage ID", true, true, FColor::Yellow, 2.f, TEXT("None"));
		return;
	}

	SelectedStageID = StageID;
	UGameplayStatics::OpenLevel(this, StageLevelNames[StageID]);
}

void UMyGameInstance::ReturnToTitle()
{
	UGameplayStatics::OpenLevel(this, FName_TitleScreen);
}

void UMyGameInstance::SaveGameData()
{
	// セーブ処理の実装(USaveGame使用)
	// パフォーマンスが必要な処理はC++で
}

void UMyGameInstance::LoadGameData()
{
	// ロード処理の実装
}


