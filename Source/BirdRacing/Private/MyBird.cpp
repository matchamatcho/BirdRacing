// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBird.h"
#include "BirdSoundComponent.h" // 作成したコンポーネントをインクルード
#include "Kismet/KismetSystemLibrary.h" //追加
#include "GameFramework/CharacterMovementComponent.h" //追加
#include <string>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



// Sets default values
AMyBird::AMyBird()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// サウンドコンポーネントを作成し、アタッチする
	SoundComponent = CreateDefaultSubobject<UBirdSoundComponent>(TEXT("SoundComponent"));

	// ブーストエフェクトコンポーネントの作成
	BoostEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BoostEffect"));
	BoostEffect->SetupAttachment(RootComponent);
	BoostEffect->bAutoActivate = false; // 初期状態では非アクティブ
	if (!BoostEffect)
	{
		//UKismetSystemLibrary::PrintString(this, "ERROR: BoostEffect component is NULL!", true, true, FColor::Red, 10.f, TEXT("None"));

	}
	else
	{
		//UKismetSystemLibrary::PrintString(this, "NOT ERROR: BoostEffect component is NULL!", true, true, FColor::Red, 10.f, TEXT("None"));

	}

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

	//直進
	AMyBird::MoveForword(DeltaTime);
	

	//重力で下に下がる
	AddMovementInput(-GetActorUpVector(), m_gravity);


}
void AMyBird::MoveForword(float DeltaTime)
{
	if (bIsBraking)
	{
		if (BrakeCharge < MaxBrakeCharge && (BrakeCharge + DeltaTime) >= MaxBrakeCharge) {
			UKismetSystemLibrary::PrintString(this, "ChargeMax!!", true, true, FColor::Cyan, 2.f, TEXT("None"));
			m_maxCharged = true;
		}
		// ブレーキ中はチャージを溜める
		BrakeCharge = FMath::Min(BrakeCharge + DeltaTime, MaxBrakeCharge);



		// 現在の速度を徐々に落とす
		GetCharacterMovement()->Velocity *= 0.98f;

		//UKismetSystemLibrary::PrintString(this, "brake-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
	else
	{
		// 常に前進する
		AddMovementInput(GetActorForwardVector(), m_forwardSpeed);
	}

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
// ブレーキ開始時に呼び出される関数
void AMyBird::StartBrake()
{
	bIsBraking = true;
	BrakeCharge = 0.0f; // チャージをリセット
	UKismetSystemLibrary::PrintString(this, "chargteStart-----", true, true, FColor::Cyan, 2.f, TEXT("None"));

	// サウンドコンポーネント経由でサウンドを再生
	if (SoundComponent)
	{
		SoundComponent->PlaySound(TEXT("Charge")); // ""という名前でサウンドを再生
		//UKismetSystemLibrary::PrintString(this, "plausound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
	else 
	{
		//UKismetSystemLibrary::PrintString(this, "notplaysound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
}

// ブレーキ解除時に呼び出される関数
void AMyBird::ReleaseBrake()
{
	bIsBraking = false;

	// チャージ量に基づいてブースト力を計算
	const float BoostScale = FMath::Clamp(BrakeCharge / MaxBrakeCharge, 0.0f, 1.0f);
	const FVector BoostVelocity = GetActorForwardVector() * BoostImpulse * BoostScale;

	
	// キャラクターの速度を直接設定して加速させる
	GetCharacterMovement()->Velocity = BoostVelocity;

	BrakeCharge = 0.0f; // チャージをリセット

	// サウンドコンポーネント経由でサウンドを再生
	if (SoundComponent)
	{
		if(m_maxCharged)
		{
			SoundComponent->PlaySound(TEXT("Boost")); // "Boost"という名前でサウンドを再生
			// エフェクトを再生
			if (BoostEffect)
			{
				BoostEffect->Activate(true);
				UKismetSystemLibrary::PrintString(this, "BoostEffect Activated!", true, true, FColor::Green, 2.f, TEXT("None"));

			}
		}
		m_maxCharged = false;
		//UKismetSystemLibrary::PrintString(this, "plausound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
	else 
	{
		//UKismetSystemLibrary::PrintString(this, "notplaysound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
}



//上下の視点移動
void AMyBird::LookUp(float Value)
{
    // Valueの値を表示
    //UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("LookUp Value: %f"), Value), true, true, FColor::Cyan, 2.f, TEXT("None"));

	if (Controller)
	{
		FRotator ControlRot = Controller->GetControlRotation();
		FString AngleStr = FString::Printf(TEXT("Pitch: %.2f, Yaw: %.2f, Roll: %.2f"), ControlRot.Pitch, ControlRot.Yaw, ControlRot.Roll);
		//UKismetSystemLibrary::PrintString(this, AngleStr, true, true, FColor::Yellow, 2.f, TEXT("None"));
	}
    if (Value == 0.0f || Controller == nullptr)
    {
        return;

    }
	

    FRotator ControlRot = Controller->GetControlRotation();

    float NewPitch = ControlRot.Pitch + (Value * m_upRotationSpeed);
    NewPitch = FRotator::NormalizeAxis(NewPitch);
    NewPitch = FMath::Clamp(NewPitch, -80.0f, 80.0f);

    ControlRot.Pitch = NewPitch;
    ControlRot.Roll = 0.0f;

    Controller->SetControlRotation(ControlRot);
	//AddControllerPitchInput(Value * m_upRotationSpeed);
}


// Called to bind functionality to input
void AMyBird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// "MoveRight" 軸と MoveRight 関数をバインドする
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyBird::RotateRight);

	// MoveUp軸と MoveUp 関数をバインドする
	PlayerInputComponent->BindAxis("MoveUp", this, &AMyBird::MoveUp);

	// ブレーキアクションをバインドする
	PlayerInputComponent->BindAction("Brake", IE_Pressed, this, &AMyBird::StartBrake);
	PlayerInputComponent->BindAction("Brake", IE_Released, this, &AMyBird::ReleaseBrake);

	//上下の視点移動をバインドする
	PlayerInputComponent->BindAxis("LookUp",this,&AMyBird::LookUp);


}

void AMyBird::AddCoin(int32 Amount)
{
	// サウンドコンポーネント経由でサウンドを再生
	if (SoundComponent)
	{
		SoundComponent->PlaySound(TEXT("GetCoin")); // ""という名前でサウンドを再生
		//UKismetSystemLibrary::PrintString(this, "plausound-----", true, true, FColor::Cyan, 2.f, TEXT("None"));
	}
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("GetCoin: %d"), Amount), true, true, FColor::Cyan, 2.f, TEXT("None"));
}
