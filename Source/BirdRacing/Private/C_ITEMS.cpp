// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ITEMS.h"
#include "Kismet/KismetSystemLibrary.h" //追加

// Sets default values
AC_ITEMS::AC_ITEMS()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_ITEMS::BeginPlay()
{
	Super::BeginPlay();
	//UKismetSystemLibrary::PrintString(this, "-------GAMESTART-----------", true, true, FColor::Cyan, 2.f, TEXT("None"));

	// オーバーラップイベントをバインド
	AC_ITEMS::BindOverlapEvents();
	
}

void AC_ITEMS::BindOverlapEvents()
{
	// ブループリントで設定されたコリジョンコンポーネントを取得
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	if (PrimitiveComponents.Num() == 0)
	{
		//UKismetSystemLibrary::PrintString(this, TEXT("WARNING: No PrimitiveComponents found!"),	true, true, FColor::Red, 5.f);
		return;
	}

	// 各コンポーネントにイベントをバインド
	for (UPrimitiveComponent* Component : PrimitiveComponents)
	{
		if (Component)
		{
			// コリジョン設定の詳細をログ出力
			//FString CollisionInfo = FString::Printf(TEXT("Component: %s\n  GenerateOverlap: %s\n  CollisionEnabled: %d\n  ObjectType: %d"),*Component->GetName(),Component->GetGenerateOverlapEvents() ? TEXT("YES") : TEXT("NO"),(int32)Component->GetCollisionEnabled(),(int32)Component->GetCollisionObjectType());
			//UKismetSystemLibrary::PrintString(this, CollisionInfo, true, true, FColor::Yellow, 5.f);

			if (Component->GetGenerateOverlapEvents())
			{
				Component->OnComponentBeginOverlap.AddDynamic(this, &AC_ITEMS::OnOverlapBegin);
				//UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Bound overlap event to: %s"), *Component->GetName()),true, true, FColor::Green, 2.f);

				// Pawnチャンネルへのレスポンスを確認
				ECollisionResponse PawnResponse = Component->GetCollisionResponseToChannel(ECC_Pawn);
				//UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("  Response to Pawn: %d (2=Overlap)"), (int32)PawnResponse),true, true, FColor::Orange, 3.f);
			}
			else
			{
				UKismetSystemLibrary::PrintString(this,
					TEXT("WARNING: GenerateOverlapEvents is FALSE!"),
					true, true, FColor::Red, 5.f);
			}
		}
	}
}

// Called every frame
void AC_ITEMS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AC_ITEMS::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// 効果を適用
		ApplyEffectToPlayer(OtherActor);
		ApplyToManager();

	}
	//UKismetSystemLibrary::PrintString(this,"Overlap", true, true, FColor::Cyan, 2.f, TEXT("None"));
}
void AC_ITEMS::ApplyEffectToPlayer(AActor* Target)
{
	// 基底クラスでは何もしない(子クラスでオーバーライド)
}
void AC_ITEMS::ApplyToManager()
{

}

