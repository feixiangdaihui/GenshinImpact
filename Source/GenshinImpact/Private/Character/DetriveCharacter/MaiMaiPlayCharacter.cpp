// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DetriveCharacter/MaiMaiPlayCharacter.h"
#include "Projectile/BallProjectile.h"
#include "PlayerComponent/ProjectileComponent.h"
#include "PlayerComponent/BlueComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "EnhancedInputComponent.h"
#include "PlayerComponent/AttackPowerComponent.h"
#include "GlobalTypes/GlobalTypes.h"
#include "PlayerComponent\ElementComponent.h"



AMaiMaiPlayCharacter::AMaiMaiPlayCharacter()
{
	IsCastingSpell = false;
	IsNormalAttack = false;
	
	NormalAttackProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("NormalAttackProjectileComponent"));
	NormalAttackProjectileComponent->SetupAttachment(RootComponent);
	CastSpellProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("CastSpellProjectileComponent"));
	CastSpellProjectileComponent->SetupAttachment(RootComponent);
}

void AMaiMaiPlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RecoverBlueByTick();
	ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->UpdateHud();
	}
}

void AMaiMaiPlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMaiMaiPlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Started, this, &AMaiMaiPlayCharacter::CastSpell);
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Started, this, &AMaiMaiPlayCharacter::NormalAttack);
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Completed, this, &AMaiMaiPlayCharacter::NormalAttackEnd);
		EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Completed, this, &AMaiMaiPlayCharacter::CastSpellEnd);
	}
}

void AMaiMaiPlayCharacter::CastSpell()
{
	if (IsAnimForbidden)
	{
		return;
	}
	IsCastingSpell = true;
}

void AMaiMaiPlayCharacter::CastSpellEnd()
{
	IsCastingSpell = false;
}

void AMaiMaiPlayCharacter::NormalAttack()
{
	if (IsAnimForbidden)
	{
		return;
	}
	IsNormalAttack = true;
}

void AMaiMaiPlayCharacter::NormalAttackEnd()
{
	IsNormalAttack = false;
}

void AMaiMaiPlayCharacter::SpawnNormalAttackProjectile()
{
	//直线发射，限制距离，距离一到自动销毁
//
	FVector InitialLocation = NormalAttackProjectileComponent->GetComponentLocation();
	FVector SpawnLocation = InitialLocation + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();
	TSubclassOf<ABallProjectile> ProjectileClass = NormalAttackProjectileComponent->ProjectileClass;
	ABallProjectile* Projectile = GetWorld()->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	Projectile->SetDamage(UGlobalTypes::CalculateDamage(AttackPowerComponent->GetAttackPower(), ElementComponent->GetElementPower())* NormalAttackRate);

}

void AMaiMaiPlayCharacter::SpawnCastSpell()
{
	if (!BlueComponent->ReduceBlue(CastSpellBlueCost))
	{
		return;
	}
	FVector InitialLocation = CastSpellProjectileComponent->GetComponentLocation();
	FVector SpawnLocation = InitialLocation + GetActorForwardVector();
	FRotator SpawnRotation = GetActorRotation();
	TSubclassOf<ABallProjectile> ProjectileClass = CastSpellProjectileComponent->ProjectileClass;
	ABallProjectile* Projectile = GetWorld()->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	Projectile->SetDamage(UGlobalTypes::CalculateDamage(AttackPowerComponent->GetAttackPower(), ElementComponent->GetElementPower())*CastSpellRate);
}



