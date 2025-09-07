// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBird.h"
#include "BirdSoundComponent.h" // �쐬�����R���|�[�l���g���C���N���[�h
#include "Kismet/KismetSystemLibrary.h" //�ǉ�
#include "GameFramework/CharacterMovementComponent.h" //�ǉ�


// Sets default values
AMyBird::AMyBird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �T�E���h�R���|�[�l���g���쐬���A�A�^�b�`����
	SoundComponent = CreateDefaultSubobject<UBirdSoundComponent>(TEXT("SoundComponent"));


}

// Called when the game starts or when spawned
void AMyBird::BeginPlay()
{
	Super::BeginPlay();

	
	// ��s���[�h�ɐݒ�
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	// �ő��s���x��ݒ�
	GetCharacterMovement()->MaxFlySpeed = 2000.0f;
	//UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f, TEXT("None"));

}
	

// Called every frame
void AMyBird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f, TEXT("None"));
	if (bIsBraking)
	{
		if (BrakeCharge < MaxBrakeCharge && (BrakeCharge + DeltaTime) >= MaxBrakeCharge){
			UKismetSystemLibrary::PrintString(this, "ChargeMax!!", true, true, FColor::Cyan, 2.f, TEXT("None"));
		}
		// �u���[�L���̓`���[�W�𗭂߂�
		BrakeCharge = FMath::Min(BrakeCharge + DeltaTime, MaxBrakeCharge);

		

		// ���݂̑��x�����X�ɗ��Ƃ�
		GetCharacterMovement()->Velocity *= 0.98f;

		//UKismetSystemLibrary::PrintString(this, "brake-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
	else
	{
		// ��ɑO�i����
		AddMovementInput(GetActorForwardVector(), m_forwardSpeed);
	}

	//�d�͂ŉ��ɉ�����
	AddMovementInput(-GetActorUpVector(), m_gravity);


}
// ���E�̉�]����������֐��̎���
void AMyBird::RotateRight(float Value)
{
	if (Value != 0.0f)
	{
		// ���E�ɉ�]����
		AddControllerYawInput(Value*m_rotationSpeed);
	}
}

// �㉺�̈ړ�����������֐��̎���
void AMyBird::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		// ��Ɉړ�
		AddMovementInput(GetActorUpVector(), Value*m_upSpeed);
		//UKismetSystemLibrary::PrintString(this, "C++ Move Up!", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
}
// �u���[�L�J�n���ɌĂяo�����֐�
void AMyBird::StartBrake()
{
	bIsBraking = true;
	BrakeCharge = 0.0f; // �`���[�W�����Z�b�g
	UKismetSystemLibrary::PrintString(this, "chargteStart-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
}

// �u���[�L�������ɌĂяo�����֐�
void AMyBird::ReleaseBrake()
{

	bIsBraking = false;

	// �`���[�W�ʂɊ�Â��ău�[�X�g�͂��v�Z
	const float BoostScale = FMath::Clamp(BrakeCharge / MaxBrakeCharge, 0.0f, 1.0f);
	const FVector BoostVelocity = GetActorForwardVector() * BoostImpulse * BoostScale;

	
	// �L�����N�^�[�̑��x�𒼐ڐݒ肵�ĉ���������
	GetCharacterMovement()->Velocity = BoostVelocity;

	BrakeCharge = 0.0f; // �`���[�W�����Z�b�g

	// �T�E���h�R���|�[�l���g�o�R�ŃT�E���h���Đ�
	if (SoundComponent)
	{
		SoundComponent->PlaySound(TEXT("Boost")); // "Boost"�Ƃ������O�ŃT�E���h���Đ�
		UKismetSystemLibrary::PrintString(this, "plausound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
	else {
		UKismetSystemLibrary::PrintString(this, "notplaysound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
		
	}
}


// Called to bind functionality to input
void AMyBird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// "MoveRight" ���� MoveRight �֐����o�C���h����
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBird::RotateRight);

	// MoveUp���� MoveUp �֐����o�C���h����
	PlayerInputComponent->BindAxis("MoveUp", this, &AMyBird::MoveUp);

	// �u���[�L�A�N�V�������o�C���h����
	PlayerInputComponent->BindAction("Brake", IE_Pressed, this, &AMyBird::StartBrake);
	PlayerInputComponent->BindAction("Brake", IE_Released, this, &AMyBird::ReleaseBrake);


}

