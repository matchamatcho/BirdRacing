// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBird.generated.h"

// 前方宣言
class UInputAction;
class UInputMappingContext;

// キャラクターの状態を表す列挙型
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

	// ブレーキ開始時に呼び出される関数
	void StartBrake();

	// ブレーキ解除時に呼び出される関数
	void ReleaseBrake();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 左右の移動を処理する関数の宣言
	void RotateRight(float Value);

	// 上下の移動を処理する関数の宣言
	void MoveUp(float Value);

private:
	float m_forwardSpeed = 100.0f; // 前進速度
	float m_rotationSpeed = 1.0f; // 回転速度
	float m_upSpeed = 100.0f; // 上下移動速度
	float m_gravity = 10.0f; // 重力の強さ

	bool bIsBraking = false; // ブレーキ中かどうかのフラグ
	float BrakeCharge = 0.0f; // 現在のチャージ量
	float MaxBrakeCharge = 2.0f; // 最大チャージ時間（秒）
	float BoostImpulse = 5000.0f; // ブースト時の力

};
