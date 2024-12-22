#include "Character/PlayCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PlayerComponent/HealthComponent.h"
#include "Projectile/BallProjectile.h"
#include "PlayerComponent/ProjectileComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/BlueComponent.h"
#include "PlayerComponent/ElementComponent.h"
#include "PlayerComponent/AttackPowerComponent.h"
#include "PlayerComponent/EquipmentBarComponent.h"
#include "PlayerComponent/LevelComponent.h"
#include "GameSave/MyGameInstance.h"

APlayCharacter::APlayCharacter()
{
	IsAnimForbidden = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));
	EquipmentBarComponent = CreateDefaultSubobject<UEquipmentBarComponent>(TEXT("EquipmentBarComponent"));
	ElementComponent = CreateDefaultSubobject<UElementComponent>(TEXT("ElementComponent"));
	AttackPowerComponent = CreateDefaultSubobject<UAttackPowerComponent>(TEXT("AttackPowerComponent"));
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));
	PickUpDistance = 1000;
}

void APlayCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	RecoverBlueByTick();

}

void APlayCharacter::BeginPlay()
{
    Super::BeginPlay();
    
	
}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Started, this, &APlayCharacter::CastSpell);
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Started, this, &APlayCharacter::NormalAttack);
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Completed, this, &APlayCharacter::NormalAttackEnd);
		EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Completed, this, &APlayCharacter::CastSpellEnd);
		EnhancedInputComponent->BindAction(ChangeCharacterAction, ETriggerEvent::Started, this, &APlayCharacter::SeqChangeCharacter);
		EnhancedInputComponent->BindAction(WearEquipmentAction, ETriggerEvent::Started, this, &APlayCharacter::WearEquipment);
	}
}

void APlayCharacter::Move(const FInputActionValue& Value)
{
	if (IsAnimForbidden)
	{
		return;
	}
	Super::Move(Value);
}
void APlayCharacter::TakeDamageByValue_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Character TakeDamageByValue"));
}
void APlayCharacter::Die_Implementation()
{
	IsDead = true;
	SeqChangeCharacter();
	
}
void APlayCharacter::RecoverBlueByTick()
{
	if (BlueComponent)
		BlueComponent->RecoverBlueByTick();
}
inline GElement APlayCharacter::GetElementType()
{
	return ElementComponent->GetElementType();
}

void APlayCharacter::WearEquipment(AEquipment* Equipment)
{
	if (EquipmentBarComponent)
	{
		EquipmentBarComponent->WearEquipment(Equipment);
	}
}

void APlayCharacter::CastSpell()
{
	if (IsAnimForbidden)
	{
		return;
	}
	if (BlueComponent->ReduceBlue(CastSpellBlueCost))
	{
		IsCastingSpell = true;
	}
}

void APlayCharacter::CastSpellEnd()
{
	IsCastingSpell = false;
}

void APlayCharacter::NormalAttack()
{
	if (IsAnimForbidden)
	{
		return;
	}
	IsNormalAttack = true;
}

void APlayCharacter::NormalAttackEnd()
{
	IsNormalAttack = false;
}

void APlayCharacter::WearEquipment()
{
	if (EquipmentBarComponent)
	{
		//拾起玩家附近最近的装备
		//获取玩家附近一个区域内的所有装备
		FVector CharacterLocation = GetActorLocation();

		TArray<FHitResult> HitResults;

		// 定义一个碰撞形状
		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(PickUpDistance);

		// 执行球形overlap检测
		bool bHasOverlapped = GetWorld()->SweepMultiByChannel(
			HitResults,
			CharacterLocation,
			CharacterLocation,
			FQuat::Identity,
			ECC_GameTraceChannel1,
			CollisionShape
		);
		for (FHitResult& HitResult : HitResults)
		{
			AEquipment* Equipment = Cast<AEquipment>(HitResult.GetActor());
			//如果是装备
			if (Equipment)
			{
				WearEquipment(Equipment);
				break;
			}
		}
		
	}
}


void APlayCharacter::LoadCharacterData(FCharacterData& InitData)
{
	
	HealthComponent->InitializeHealthComponent(InitData.CurrentHealth);
	if (InitData.CurrentHealth <= 0)
		IsDead = true;
	BlueComponent->InitializeBlueComponent(InitData.CurrentBlue); 
	LevelComponent->InitializeLevelComponent(InitData.CurrentLevel, InitData.CurrentExperience);
	for (int i = 0; i < InitData.EquipmentBarClass.Num(); i++)
	{
		//根据类名生成装备
		FString EquipmentClassName = InitData.EquipmentBarClass[i];
		UClass* EquipmentClass = StaticLoadClass(AEquipment::StaticClass(), nullptr, *EquipmentClassName);
		if (EquipmentClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Load Equipment %s"), *EquipmentClassName);
			AEquipment* Equipment = GetWorld()->SpawnActor<AEquipment>(EquipmentClass);
			if (Equipment)
			{
				WearEquipment(Equipment);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn equipment of class %s"), *EquipmentClassName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load class %s"), *EquipmentClassName);
		}
	}

}

FCharacterData  APlayCharacter::SaveCharacterData()
{
	FCharacterData CharacterData;
	CharacterData.CurrentHealth = HealthComponent->GetCurrentHealth();

	CharacterData.CurrentBlue = BlueComponent->GetCurrentBlue();
	CharacterData.CurrentExperience = LevelComponent->GetCurrentExperience();
	CharacterData.CurrentLevel = LevelComponent->GetCurrentLevel();
	for (auto Equipment : EquipmentBarComponent->EquipmentBar)
	{
		if (Equipment)
		{
			CharacterData.EquipmentBarClass.Add(Equipment->GetClass()->GetPathName());
		}
	}
	return CharacterData;
}






void APlayCharacter::SeqChangeCharacter()
{
	ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->SeqChangeCharacter();
	}
}
void APlayCharacter::TakeOffEquipment(EEquipmentType EquipmentType)
{
	if (EquipmentBarComponent)
	{
		EquipmentBarComponent->TakeOffEquipment(EquipmentType);
	}
}

inline int APlayCharacter::GetLevel() const
{
	return LevelComponent->GetCurrentLevel();
}

