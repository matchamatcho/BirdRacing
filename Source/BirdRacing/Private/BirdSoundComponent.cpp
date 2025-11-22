// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdSoundComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UBirdSoundComponent::UBirdSoundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



void UBirdSoundComponent::PlaySound(FName SoundName)
{
	// SoundMapから指定された名前のサウンドを探す
	if (USoundBase** FoundSound = SoundMap.Find(SoundName))
	{
		if (*FoundSound)
		{
			// 既に同じ名前のサウンドが再生中なら停止
			if (UAudioComponent** ExistingComponent = ActiveAudioComponents.Find(SoundName))
			{
				if (*ExistingComponent && (*ExistingComponent)->IsPlaying())
				{
					(*ExistingComponent)->Stop();
				}
			}

			// オーディオコンポーネントを作成して再生
			UAudioComponent* AudioComp = UGameplayStatics::SpawnSoundAtLocation(
				GetWorld(), 
				*FoundSound, 
				GetOwner()->GetActorLocation(),
				FRotator::ZeroRotator,
				1.0f,
				1.0f,
				0.0f,
				nullptr,
				nullptr,
				true // bAutoDestroy = true
			);

			if (AudioComp)
			{
				ActiveAudioComponents.Add(SoundName, AudioComp);
			}
		}
		else 
		{
			UKismetSystemLibrary::PrintString(this, "NOT:UBirdSoundComponent::PlaySound", true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
	}
	else 
	{
		UKismetSystemLibrary::PrintString(this, "Sound not find", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
}

void UBirdSoundComponent::StopSound(FName SoundName)
{
	// アクティブなオーディオコンポーネントを検索
	if (UAudioComponent** FoundComponent = ActiveAudioComponents.Find(SoundName))
	{
		if (*FoundComponent && (*FoundComponent)->IsPlaying())
		{
			(*FoundComponent)->Stop();
		}
		ActiveAudioComponents.Remove(SoundName);
	}
}

void UBirdSoundComponent::DebugPrintSoundMapKeys()
{
	if (SoundMap.Num() == 0)
	{
		UKismetSystemLibrary::PrintString(this, "SoundMap is EMPTY!", true, true, FColor::Red, 5.f, TEXT("None"));
		return;
	}

	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("SoundMap has %d entries:"), SoundMap.Num()), true, true, FColor::Yellow, 5.f, TEXT("None"));

	for (const auto& Pair : SoundMap)
	{
		FString SoundAssetName = Pair.Value ? Pair.Value->GetName() : TEXT("NULL");
		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("  Key: '%s' -> Sound: %s"), *Pair.Key.ToString(), *SoundAssetName), true, true, FColor::Cyan, 5.f, TEXT("None"));
	}
}