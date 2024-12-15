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

}

void AMaiMaiPlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMaiMaiPlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void AMaiMaiPlayCharacter::SpawnNormalAttack()
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

	FVector InitialLocation = CastSpellProjectileComponent->GetComponentLocation();
	FVector SpawnLocation = InitialLocation + GetActorForwardVector();
	FRotator SpawnRotation = GetActorRotation();
	TSubclassOf<ABallProjectile> ProjectileClass = CastSpellProjectileComponent->ProjectileClass;
	ABallProjectile* Projectile = GetWorld()->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	Projectile->SetDamage(UGlobalTypes::CalculateDamage(AttackPowerComponent->GetAttackPower(), ElementComponent->GetElementPower())*CastSpellRate);
}



