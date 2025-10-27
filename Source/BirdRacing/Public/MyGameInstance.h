// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class BIRDRACING_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UMyGameInstance();

    // ========================================
    // C++で実装すべき部分
    // ========================================
    
    // レベル遷移ロジック(複雑な処理)
    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadStageSelect();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadStage(int32 StageID);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void ReturnToTitle();

    // セーブ/ロード処理(パフォーマンス重視)
    UFUNCTION(BlueprintCallable, Category = "Save")
    void SaveGameData();

    UFUNCTION(BlueprintCallable, Category = "Save")
    void LoadGameData();

    // ========================================
    // Blueprintで編集可能にする部分
    // ========================================
    
    // ゲームデータ(デザイナーが調整する値)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
    int32 SelectedStageID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
    int32 TotalCoins;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
    TArray<bool> UnlockedStages;

    // レベル名のマッピング(エディタで設定)
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Levels")
    TMap<int32, FName> StageLevelNames;

protected:
    virtual void Init() override;

private:
    // 内部的なヘルパー関数(C++のみ)
    void InitializeDefaultData();
    FName FName_SelectStage;
    FName FName_TitleScreen;
};
