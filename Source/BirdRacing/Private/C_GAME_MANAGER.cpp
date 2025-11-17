// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GAME_MANAGER.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



void UC_GAME_MANAGER::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RemainingTime = 0.0f;
	bIsFinished = false;
}

void UC_GAME_MANAGER::Deinitialize()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}
	Super::Deinitialize();
}

void UC_GAME_MANAGER::StartGame(float TimeLimit)
{
	RemainingTime = TimeLimit;
	bIsFinished = false;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TimerHandle, this, &UC_GAME_MANAGER::UpdateTimer, 0.1f, true);
	}
}

void UC_GAME_MANAGER::UpdateTimer()
{
	RemainingTime -= 0.1f;

	if (RemainingTime <= 0.0f)
	{
		FinishGame();
	}
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("left time: %f"), RemainingTime), true, true, FColor::Cyan, 5.f, TEXT("None"));

}

void UC_GAME_MANAGER::FinishGame()
{
	bIsFinished = true;
	RemainingTime = 0.0f;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

	// イベントを発行(UIがこれを受け取って"FINISH"を表示)
	OnGameFinished.Broadcast();
}