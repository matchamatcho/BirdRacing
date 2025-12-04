// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ITEMS_COIN.h"
#include "MyBird.h"
#include "C_GAME_STATE_BASE.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h" //追加


AC_ITEMS_COIN::AC_ITEMS_COIN() 
{
	CoinValue = 1;
	TimeBonus = 3.0f; // デフォルトで3秒追加

}

void AC_ITEMS_COIN::ApplyEffectToPlayer(AActor* Target)
{
	AMyBird* Player = Cast<AMyBird>(Target);
	if (Player)
	{
		Player->AddCoin(CoinValue);


		// GameStateを取得して時間を追加
		AC_GAME_STATE_BASE* GameState = Cast<AC_GAME_STATE_BASE>(GetWorld()->GetGameState());
		if (GameState)
		{
			GameState->AddRemainingTime(TimeBonus);
			//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Time Added: +%.1f seconds"), TimeBonus), true, true, FColor::Green, 2.f, TEXT("None"));
		}

		Destroy();

	}


}
void AC_ITEMS_COIN::ApplyToManager()
{
	if (m_OwnerSpawner)
	{
		m_OwnerSpawner->OnCoinCollected();
	}
	else
	{
		//UKismetSystemLibrary::PrintString(this, "COIN SPORNNER NOT FOUND", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}


}

