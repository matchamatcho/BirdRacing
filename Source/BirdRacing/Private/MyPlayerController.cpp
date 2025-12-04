// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "C_GAME_STATE_BASE.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	CachedGameState = nullptr;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// GameStateの参照を取得
	CachedGameState = Cast<AC_GAME_STATE_BASE>(GetWorld()->GetGameState());
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Rキーにリスタート機能をバインド
	InputComponent->BindAction("Restart", IE_Pressed, this, &AMyPlayerController::RestartLevel);
}

void AMyPlayerController::RestartLevel()
{
	// GameStateがタイムアップ状態の場合のみリスタート
	if (CachedGameState && CachedGameState->GetCurrentGameState() == EGameState::TimeUp)
	{
		// 現在のレベル名を取得
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
		
		// レベルを再読み込み
		UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
	}
}

