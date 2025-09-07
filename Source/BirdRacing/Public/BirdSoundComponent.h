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

	// �w�肳�ꂽ���O�̃T�E���h���Đ�����
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySound(FName SoundName);

protected:

	// �Đ��������T�E���h�𖼑O�ƃA�Z�b�g�̃y�A�œo�^����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TMap<FName, USoundBase*> SoundMap;

		
};
