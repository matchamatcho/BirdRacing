// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ITEMS_COIN.h"
#include "MyBird.h"
#include "Kismet/KismetSystemLibrary.h" //’Ç‰Á


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

