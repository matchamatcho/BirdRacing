// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
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

	// 指定された名前のサウンドを停止する
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopSound(FName SoundName);

	// デバッグ用: サウンドマップのキーを全て出力
	void DebugPrintSoundMapKeys();

protected:

	// 再生したいサウンドを名前とアセットのペアで登録する
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TMap<FName, USoundBase*> SoundMap;

private:
	// 再生中のオーディオコンポーネントを管理
	UPROPERTY()
	TMap<FName, UAudioComponent*> ActiveAudioComponents;

		
};
