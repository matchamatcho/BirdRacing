// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_COIN_SPONNER.generated.h"

UCLASS()
class BIRDRACING_API AC_COIN_SPONNER : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_COIN_SPONNER();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// コインが収集されたときに呼ばれる関数
	UFUNCTION(BlueprintCallable, Category = "Coin")
	void OnCoinCollected();

	// スポーンするコインのクラス
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	TSubclassOf<AActor> CoinClass;

	// 同時に存在するコインの最大数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 m_MaxCoins = 10;

	// スポーン範囲の最小値
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	FVector m_SpawnMin = FVector(-1000.0f, -1000.0f, 100.0f);

	// スポーン範囲の最大値
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	FVector m_SpawnMax = FVector(1000.0f, 1000.0f, 500.0f);
private:
	// スポーン済みのコインを追跡
	UPROPERTY()
	TArray<AActor*> m_SpawnedCoins;

	// ランダムな位置にコインを1枚スポーン
	void SpawnCoin();

	// ランダムな位置を取得
	FVector GetRandomSpawnLocation() const;
};
