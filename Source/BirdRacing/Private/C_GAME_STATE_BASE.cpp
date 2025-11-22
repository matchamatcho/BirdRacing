// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GAME_STATE_BASE.h"
#include "Kismet/KismetSystemLibrary.h" //’Ç‰Á


AC_GAME_STATE_BASE::AC_GAME_STATE_BASE()
{
	PrimaryActorTick.bCanEverTick = true;
	RemainingTime = 0.0f;
	bIsCountingDown = false;
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
}
void AC_GAME_STATE_BASE::StartCountdown()
{
	RemainingTime = m_MaxTime;
	bIsCountingDown = true;
}

void AC_GAME_STATE_BASE::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsCountingDown)
	{
		return;
	}

	RemainingTime -= DeltaSeconds;

	// ‰æ–Ê‚ÉŽc‚èŽžŠÔ‚ð•\Ž¦
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, FString::Printf(TEXT("Remaining Time: %.1f"), RemainingTime));
	}

	if (RemainingTime <= 0.0f)
	{
		RemainingTime = 0.0f;
		bIsCountingDown = false;
		OnTimeUp.Broadcast();
	}
}

