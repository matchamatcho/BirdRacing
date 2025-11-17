// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "C_GAME_MANAGER.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFinished);

/**
 * ゲーム全体の制限時間とゲーム状態を管理
 */
UCLASS()
class BIRDRACING_API UC_GAME_MANAGER : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// 制限時間が終了した時のイベント
	UPROPERTY(BlueprintAssignable,Category="Game")
	FOnGameFinished OnGameFinished;

	// ゲーム開始
	UFUNCTION(BlueprintCallable,Category="Game")
	void StartGame(float TimeLimit);

	// 残り時間を取得
	UFUNCTION(BlueprintPure, Category = "Game")
	float GetRemainingTime() const { return RemainingTime; }

	// ゲームが終了しているか
	UFUNCTION(BlueprintPure, Category = "Game")
	bool IsGameFinished() const { return bIsFinished; }

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	UPROPERTY()
	float RemainingTime;

	UPROPERTY()
	bool bIsFinished;

	FTimerHandle TimerHandle;

	void UpdateTimer();
	void FinishGame();
};
