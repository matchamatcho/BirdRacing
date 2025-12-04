// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_ITEMS.h"
#include "C_COIN_SPONNER.h"
#include "C_ITEMS_COIN.generated.h"


/**
 * 
 */
UCLASS()
class BIRDRACING_API AC_ITEMS_COIN : public AC_ITEMS
{
	GENERATED_BODY()
public:
	AC_ITEMS_COIN();

protected:
	// コインの価値
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Effect")
	int32 CoinValue;

	// コイン取得時に追加される時間（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin Settings")
	float TimeBonus = 3.0f;

	UPROPERTY()
	class AC_COIN_SPONNER* m_OwnerSpawner;

	virtual void ApplyEffectToPlayer(AActor* Target) override;
	virtual void ApplyToManager() override;
	// C_ITEMS_COIN.h に追加
public:
	void SetOwnerSpawner(AC_COIN_SPONNER* Spawner) { m_OwnerSpawner = Spawner; }

	
};
