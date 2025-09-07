// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BirdSoundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIRDRACING_API UBirdSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBirdSoundComponent();

	// 指定された名前のサウンドを再生する
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySound(FName SoundName);

protected:

	// 再生したいサウンドを名前とアセットのペアで登録する
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TMap<FName, USoundBase*> SoundMap;

		
};
