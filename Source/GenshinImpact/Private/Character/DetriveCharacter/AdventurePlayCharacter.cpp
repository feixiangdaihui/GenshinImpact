// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DetriveCharacter/AdventurePlayCharacter.h"
#include "Components/BoxComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "GlobalTypes/GlobalTypes.h"
#include "PlayerComponent/AttackPowerComponent.h"
#include "PlayerComponent/ElementComponent.h"

AAdventurePlayCharacter::AAdventurePlayCharacter()
{
	NormalAttackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("NormalAttackCollisionComponent"));
	NormalAttackCollisionComponent->SetupAttachment(GetMesh(), TEXT("NormalAttack"));
	NormalAttackCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	NormalAttackCollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	NormalAttackCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	NormalAttackCollisionComponent->SetBoxExtent(FVector(150.0f, 50.0f, 50.0f));
	NormalAttackCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAdventurePlayCharacter::NormalAttackCollisionBeginOverlap);
	SpellRangeDia = 100;
}

void AAdventurePlayCharacter::SpawnNormalAttack()
{
}

void AAdventurePlayCharacter::SpawnCastSpell()
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
				UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), ActualDamage);
			}
		}
	}
}

void AAdventurePlayCharacter::NormalAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsJudgeNormalAttack)
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
				
				Enemy->TakeDamageByValue(ActualDamage);
			}
		}
	}
}
