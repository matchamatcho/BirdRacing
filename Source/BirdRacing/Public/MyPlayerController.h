// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BIRDRACING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	// ステージセレクトレベルの名前
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Management")
	FName StageSelectLevelName = FName(TEXT("SelectStages"));

private:
	// Rキーでリスタート
	void RestartLevel();

	void ReturnToStageSelect();

	// GameStateの参照
	UPROPERTY()
	class AC_GAME_STATE_BASE* CachedGameState;

	
};
