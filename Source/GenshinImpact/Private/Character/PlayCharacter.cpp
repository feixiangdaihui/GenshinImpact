// Fill out your copyright notice in the Description page of Project Settings.


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

APlayCharacter::APlayCharacter()
{
	IsAnimForbidden = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));
	EquipmentBarComponent = CreateDefaultSubobject<UEquipmentBarComponent>(TEXT("EquipmentBarComponent"));
	ElementComponent = CreateDefaultSubobject<UElementComponent>(TEXT("ElementComponent"));
	AttackPowerComponent = CreateDefaultSubobject<UAttackPowerComponent>(TEXT("AttackPowerComponent"));
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));

}

void APlayCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void APlayCharacter::BeginPlay()
{
    Super::BeginPlay();
    //输入初始化
}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	UE_LOG(LogTemp, Warning, TEXT("Character Die"));
	//退出游戏
	
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
		HealthComponent->UpdateMaxHealth();
		ElementComponent->UpdateElementPower();
		AttackPowerComponent->UpdateAttackPower();
	}
}

void APlayCharacter::TakeOffEquipment(EEquipmentType EquipmentType)
{
	if (EquipmentBarComponent)
	{
		EquipmentBarComponent->TakeOffEquipment(EquipmentType);
		HealthComponent->UpdateMaxHealth();
		ElementComponent->UpdateElementPower();
		AttackPowerComponent->UpdateAttackPower();
	}
}

inline int APlayCharacter::GetLevel() const
{
	return LevelComponent->level;
}

