// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GAME_STATE_BASE.h"
#include "Kismet/KismetSystemLibrary.h" //追加


AC_GAME_STATE_BASE::AC_GAME_STATE_BASE()
{
	PrimaryActorTick.bCanEverTick = true;
	RemainingTime = 0.0f;
	bIsCountingDown = false;
	CurrentGameState = EGameState::InProgress; // 初期状態

}

void AC_GAME_STATE_BASE::BeginPlay()
{
	Super::BeginPlay();
	AC_GAME_STATE_BASE::StartCountdown();
	UKismetSystemLibrary::PrintString(this, "---begin game state base---", true, true, FColor::Cyan, 2.f, TEXT("None"));

}

void AC_GAME_STATE_BASE::StartCountdown(float TimeLimit)
{
	RemainingTime = TimeLimit;
	bIsCountingDown = true;
	SetGameState(EGameState::InProgress); // 状態をゲーム進行中に変更

}
void AC_GAME_STATE_BASE::StartCountdown()
{
	StartCountdown(m_MaxTime);
}

void AC_GAME_STATE_BASE::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsCountingDown)
	{
		return;
	}

	RemainingTime -= DeltaSeconds;

	if (RemainingTime <= 0.0f)
	{
		RemainingTime = 0.0f;
		bIsCountingDown = false;
		OnTimeUp.Broadcast();
		SetGameState(EGameState::TimeUp); // 状態をタイムアップに変更

	}
}

// ゲーム状態を設定する関数
void AC_GAME_STATE_BASE::SetGameState(EGameState NewState)
{
	CurrentGameState = NewState;
}

void AC_GAME_STATE_BASE::AddRemainingTime(float AdditionalTime)
{
	if (bIsCountingDown)
	{
		RemainingTime += AdditionalTime;
		// 最大時間を超えないようにクランプ（オプション）
		//RemainingTime = FMath::Min(RemainingTime, m_MaxTime);
	}
}