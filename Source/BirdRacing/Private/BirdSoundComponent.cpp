// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdSoundComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

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
	// SoundMap����w�肳�ꂽ���O�̃T�E���h��T��
	if (USoundBase** FoundSound = SoundMap.Find(SoundName))
	{
		if (*FoundSound)
		{
			// �I�[�i�[�A�N�^�[�̈ʒu�ŃT�E���h���Đ�
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), *FoundSound, GetOwner()->GetActorLocation());
			UKismetSystemLibrary::PrintString(this, "UBirdSoundComponent::PlaySound", true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
		else {
			UKismetSystemLibrary::PrintString(this, "NOT:UBirdSoundComponent::PlaySound", true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
	}
	else {
		UKismetSystemLibrary::PrintString(this, "Sound not find", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
}

