// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/PrimitiveComponent.h"
#include "C_ITEMS.generated.h"

UCLASS()
class BIRDRACING_API AC_ITEMS : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ITEMS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// オーバーラップイベントをバインドする関数
	void BindOverlapEvents();

	// 子クラスでオーバーライドする効果適用関数
		virtual void ApplyEffectToPlayer(AActor * Target);

	// オーバーラップ時に呼ばれる関数
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
