// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBird.generated.h"

// �O���錾
class UInputAction;
class UInputMappingContext;

// �L�����N�^�[�̏�Ԃ�\���񋓌^
UENUM(BlueprintType)
enum class EBirdState : uint8
{
	BS_Normal	UMETA(DisplayName = "Normal"),
	BS_Braking	UMETA(DisplayName = "Braking"),
	BS_Boosting	UMETA(DisplayName = "Boosting"),
	BS_Ascending	UMETA(DisplayName = "Ascending")
};

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

	// �u���[�L�J�n���ɌĂяo�����֐�
	void StartBrake();

	// �u���[�L�������ɌĂяo�����֐�
	void ReleaseBrake();



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

	bool bIsBraking = false; // �u���[�L�����ǂ����̃t���O
	float BrakeCharge = 0.0f; // ���݂̃`���[�W��
	float MaxBrakeCharge = 2.0f; // �ő�`���[�W���ԁi�b�j
	float BoostImpulse = 5000.0f; // �u�[�X�g���̗�

};
