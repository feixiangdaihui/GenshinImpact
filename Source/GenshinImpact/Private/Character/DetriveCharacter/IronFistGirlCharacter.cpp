// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DetriveCharacter/IronFistGirlCharacter.h"
#include "Components/BoxComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "GlobalTypes/GlobalTypes.h"
#include "PlayerComponent/AttackPowerComponent.h"

#include"PlayerComponent\ElementComponent.h"
AIronFistGirlCharacter::AIronFistGirlCharacter()
{
	LeftFistCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFistCollisionComponent"));
	RightFistCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionComponent"));
	LeftFistCollisionComponent->SetupAttachment(GetMesh(), TEXT("LeftFist"));
	RightFistCollisionComponent->SetupAttachment(GetMesh(), TEXT("RightFist"));
	LeftFistCollisionComponent->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	LeftFistCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftFistCollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	LeftFistCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RightFistCollisionComponent->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	RightFistCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightFistCollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	RightFistCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//绑定事件
	LeftFistCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AIronFistGirlCharacter::FistCollisionBeginOverlap);
	RightFistCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AIronFistGirlCharacter::FistCollisionBeginOverlap);
}

void AIronFistGirlCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIronFistGirlCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AIronFistGirlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIronFistGirlCharacter::SpawnNormalAttack()
{

}

void AIronFistGirlCharacter::SpawnCastSpell()
{

	// 获取角色位置
	FVector CharacterLocation = GetActorLocation();

	// 定义一个数组来存储重叠的敌人
	TArray<FHitResult> HitResults;

	// 定义一个碰撞形状
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(SpellRangeDia);

	// 执行球形重叠检测
	bool bHasOverlapped = GetWorld()->SweepMultiByChannel(
		HitResults,
		CharacterLocation,
		CharacterLocation,
		FQuat::Identity,
		ECC_Pawn,
		CollisionShape
	);

	// 对重叠的敌人造成伤害
	if (bHasOverlapped)
	{
		for (FHitResult& HitResult : HitResults)
		{
			AActor* OverlappedActor = HitResult.GetActor();
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OverlappedActor);
			if (Enemy)
			{
				GElement EnemyElementType = Enemy->GetElementType();
				GElement CharacterElementType = GetElementType();
				int EnemyLevel = Enemy->GetLevel();
				int CharacterLevel = GetLevel();
				float BeforeDamage = UGlobalTypes::CalculateDamage(AttackPowerComponent->GetAttackPower(), ElementComponent->GetElementPower());
				BeforeDamage *= CastSpellRate;
				float ActualDamage = UGlobalTypes::ModifyDamage(BeforeDamage, EnemyLevel, CharacterLevel, EnemyElementType, CharacterElementType);
				Enemy->TakeDamageByValue(ActualDamage);

			}
		}
	}

}



void AIronFistGirlCharacter::FistCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsNormalAttack||IsCastingSpell)
	{
		if (OtherActor)
		{
			//判断OtherActor是否是敌人
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor);
			if (Enemy)
			{
				GElement EnemyElementType = Enemy->GetElementType();
				GElement CharacterElementType = GetElementType();
				int EnemyLevel = Enemy->GetLevel();
				int CharacterLevel = GetLevel();
				float BeforeDamage = UGlobalTypes::CalculateDamage(AttackPowerComponent->GetAttackPower(), ElementComponent->GetElementPower());
				BeforeDamage *= NormalAttackRate;
				float ActualDamage = UGlobalTypes::ModifyDamage(BeforeDamage, EnemyLevel, CharacterLevel, EnemyElementType, CharacterElementType);
				UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), ActualDamage);
				Enemy->TakeDamageByValue(ActualDamage);
			}
		}
	}
}
