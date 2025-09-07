// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBird.h"
#include "Kismet/KismetSystemLibrary.h" //追加
#include "GameFramework/CharacterMovementComponent.h" //追加


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

	
	// 飛行モードに設定
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	// 最大飛行速度を設定
	GetCharacterMovement()->MaxFlySpeed = 2000.0f;
	//UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f, TEXT("None"));

}
	

// Called every frame
void AMyBird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f, TEXT("None"));
	// 常に前進する
	AddMovementInput(GetActorForwardVector(),m_forwardSpeed);

	//重力で下に下がる
	AddMovementInput(-GetActorUpVector(), m_gravity);


}
// 左右の回転を処理する関数の実装
void AMyBird::RotateRight(float Value)
{
	if (Value != 0.0f)
	{
		// 左右に回転する
		AddControllerYawInput(Value*m_rotationSpeed);
	}
}

// 上下の移動を処理する関数の実装
void AMyBird::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		// 上に移動
		AddMovementInput(GetActorUpVector(), Value*m_upSpeed);
		//UKismetSystemLibrary::PrintString(this, "C++ Move Up!", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
}

// Called to bind functionality to input
void AMyBird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// "MoveRight" 軸と MoveRight 関数をバインドする
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBird::RotateRight);

	// MoveUp軸と MoveUp 関数をバインドする
	PlayerInputComponent->BindAxis("MoveUp", this, &AMyBird::MoveUp);

}

