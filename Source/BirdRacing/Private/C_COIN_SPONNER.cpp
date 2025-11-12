// Fill out your copyright notice in the Description page of Project Settings.


#include "C_COIN_SPONNER.h"
#include "Kismet/KismetSystemLibrary.h" //追加
#include "C_ITEMS_COIN.h"


// Sets default values
AC_COIN_SPONNER::AC_COIN_SPONNER()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AC_COIN_SPONNER::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::PrintString(this, "C_COIN_SPONNER_BEGINPLAY()", true, true, FColor::Cyan, 2.f, TEXT("None"));
	// ゲーム開始時に最大数のコインを一気にスポーン
	for (int32 i = 0; i < m_MaxCoins; i++)
	{
		SpawnCoin();
	}
	
}

// Called every frame
void AC_COIN_SPONNER::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_COIN_SPONNER::OnCoinCollected()
{
	UKismetSystemLibrary::PrintString(this, "C_COIN_SPONNER::OnCoinCollected()", true, true, FColor::Cyan, 2.f, TEXT("None"));
	m_SpawnedCoins.RemoveAt(0);
	// 現在のコイン数が最大数未満の場合、新しいコインをスポーン
	if (m_SpawnedCoins.Num() < m_MaxCoins)
	{
		SpawnCoin();
	}
}

void AC_COIN_SPONNER::SpawnCoin()
{
	//return;
	if (!CoinClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("CoinClass is not set in C_COIN_SPONNER!"));
		return;
	}
	UKismetSystemLibrary::PrintString(this, "COIN SPORN", true, true, FColor::Cyan, 2.f, TEXT("None"));

	// ランダムな位置を取得
	FVector SpawnLocation = GetRandomSpawnLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// スポーンパラメータを設定
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// コインをスポーン
	AActor* SpawnedCoin = GetWorld()->SpawnActor<AActor>(CoinClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (SpawnedCoin)
	{
		m_SpawnedCoins.Add(SpawnedCoin);
		//UE_LOG(LogTemp, Log, TEXT("Coin spawned at location: %s"), *SpawnLocation.ToString());
		// スポーン位置を画面に表示
		UKismetSystemLibrary::PrintString(this,
			FString::Printf(TEXT("Coin spawn at: X=%.1f Y=%.1f Z=%.1f"),
				SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z),
			true, true, FColor::Green, 2.f);
		// キャストして参照を設定
		AC_ITEMS_COIN* Coin = Cast<AC_ITEMS_COIN>(SpawnedCoin);
		if (Coin)
		{
			Coin->SetOwnerSpawner(this);  // ★ここで設定
		}
	}
}

FVector AC_COIN_SPONNER::GetRandomSpawnLocation() const
{
	float RandomX = FMath::RandRange(m_SpawnMin.X, m_SpawnMax.X);
	float RandomY = FMath::RandRange(m_SpawnMin.Y, m_SpawnMax.Y);
	float RandomZ = FMath::RandRange(m_SpawnMin.Z, m_SpawnMax.Z);

	return FVector(RandomX, RandomY, RandomZ);
}