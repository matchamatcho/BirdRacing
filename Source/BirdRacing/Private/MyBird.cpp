// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBird.h"
#include "Kismet/KismetSystemLibrary.h" //�ǉ�
#include "GameFramework/CharacterMovementComponent.h" //�ǉ�


// Sets default values
AMyBird::AMyBird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	// ��ɑO�i����
	AddMovementInput(GetActorForwardVector(),m_forwardSpeed);

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

// Called to bind functionality to input
void AMyBird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// "MoveRight" ���� MoveRight �֐����o�C���h����
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBird::RotateRight);

	// MoveUp���� MoveUp �֐����o�C���h����
	PlayerInputComponent->BindAxis("MoveUp", this, &AMyBird::MoveUp);

}

