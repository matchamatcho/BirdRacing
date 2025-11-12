// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_ITEMS.h"
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
	// ƒRƒCƒ“‚Ì‰¿’l
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Effect")
	int32 CoinValue;

	virtual void ApplyEffectToPlayer(AActor* Target);

	
};
