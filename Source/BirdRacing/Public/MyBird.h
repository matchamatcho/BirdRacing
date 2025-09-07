// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBird.generated.h"
//#include "InputActionValue.h" // �ǉ�

// �O���錾
class UInputAction;
class UInputMappingContext;

UCLASS()
class BIRDRACING_API AMyBird : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ���E�̈ړ�����������֐��̐錾
	void RotateRight(float Value);

	// �㉺�̈ړ�����������֐��̐錾
	void MoveUp(float Value);

private:
	float m_forwardSpeed = 100.0f; // �O�i���x
	float m_rotationSpeed = 1.0f; // ��]���x
	float m_upSpeed = 100.0f; // �㉺�ړ����x
	float m_gravity = 10.0f; // �d�͂̋���

};
