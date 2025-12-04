// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_GAME_STATE_BASE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeUp);


// ゲーム状態の列挙型
UENUM(BlueprintType)
enum class EGameState : uint8
{
	InProgress UMETA(DisplayName = "ゲーム進行中"),
	TimeUp UMETA(DisplayName = "タイムアップ")
};

/**
 * 
 */
UCLASS()
class BIRDRACING_API AC_GAME_STATE_BASE : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AC_GAME_STATE_BASE();

	// カウントダウン開始
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartCountdown(float TimeLimit);
	void StartCountdown();

	// 残り時間を取得
	UFUNCTION(BlueprintPure, Category = "Game")
	float GetRemainingTime() const { return RemainingTime; }

	// 現在のゲーム状態を取得
	UFUNCTION(BlueprintPure, Category = "Game")
	EGameState GetCurrentGameState() const { return CurrentGameState; }

	// ゲーム状態を設定
	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetGameState(EGameState NewState);


	// 時間切れイベント
	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnTimeUp OnTimeUp;

	// 残り時間を追加する
	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddRemainingTime(float AdditionalTime);

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	// エディタで設定可能な最大時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "0.0"))
	float m_MaxTime=10.0f;

	// 現在のゲーム状態
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	EGameState CurrentGameState;

private:
	UPROPERTY()
	float RemainingTime;

	UPROPERTY()
	bool bIsCountingDown;
};
