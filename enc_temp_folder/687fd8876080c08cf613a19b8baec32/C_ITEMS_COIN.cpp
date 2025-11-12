// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ITEMS_COIN.h"
#include "MyBird.h"

AC_ITEMS_COIN::AC_ITEMS_COIN() 
{
	CoinValue = 1;

}

void AC_ITEMS_COIN::ApplyEffectToPlayer(AActor* Target)
{
	AMyBird* Player = Cast<AMyBird>(Target);
	if (Player)
	{
		Player->AddCoin(CoinValue);
		Destroy();

	}


}


