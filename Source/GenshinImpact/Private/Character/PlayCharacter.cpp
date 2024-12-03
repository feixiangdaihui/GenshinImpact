// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PlayerComponent/HealthComponent.h"
#include "Projectile/BallProjectile.h"
#include"PlayerComponent/ProjectileComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/BlueComponent.h"
APlayCharacter::APlayCharacter()
{
	IsCastingSpell = false;
	IsNormalAttack = false;
	IsAnimForbidden = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));
	NormalAttackProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("NormalAttackProjectileComponent"));
	NormalAttackProjectileComponent->SetupAttachment(RootComponent);
	CastSpellProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("CastSpellProjectileComponent"));
	CastSpellProjectileComponent->SetupAttachment(RootComponent);

}

void APlayCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	RecoverBlueByTick();
	ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->UpdateHud();
	}

	
}


void APlayCharacter::BeginPlay()
{
    Super::BeginPlay();
    //输入初始化

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
    }
}




void APlayCharacter::CastSpell()
{
	if (IsAnimForbidden)
	{
		return;
	}
    IsCastingSpell = true;
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

void APlayCharacter::Move(const FInputActionValue& Value)
{
	if (IsAnimForbidden)
	{
		return;
	}
	Super::Move(Value);
}

void APlayCharacter::TakeDamageByValue_Implementation(float DamageAmount)
{
	HealthComponent->DamageHealthByValue(DamageAmount);
	if (HealthComponent->CurrentHealth <= 0)
	{
		Die();
	}
}

void APlayCharacter::Die_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Character Die"));
}

void APlayCharacter::SpawnNormalAttackProjectile()
{
	//直线发射，限制距离，距离一到自动销毁
	//
	FVector InitialLocation = NormalAttackProjectileComponent->GetComponentLocation();
	FVector SpawnLocation = InitialLocation + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();
	TSubclassOf<ABallProjectile> ProjectileClass = NormalAttackProjectileComponent->ProjectileClass;
	ABallProjectile* Projectile = GetWorld()->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	
}

void APlayCharacter::SpawnCastSpell()
{
	if (!BlueComponent->ReduceBlue(CastSpellBlueCost))
	{
		return;
	}
	FVector InitialLocation = CastSpellProjectileComponent->GetComponentLocation();
	FVector SpawnLocation = InitialLocation + GetActorForwardVector() ;
	FRotator SpawnRotation = GetActorRotation();
	TSubclassOf<ABallProjectile> ProjectileClass = CastSpellProjectileComponent->ProjectileClass;
	ABallProjectile* Projectile = GetWorld()->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
}

void APlayCharacter::RecoverBlueByTick()
{
	if (BlueComponent)
		BlueComponent->RecoverBlueByTick();
}
