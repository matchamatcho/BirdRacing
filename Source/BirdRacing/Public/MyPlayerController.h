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

private:
	// Rキーでリスタート
	void RestartLevel();

	// GameStateの参照
	UPROPERTY()
	class AC_GAME_STATE_BASE* CachedGameState;

	
};
