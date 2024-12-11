#include "Character/PlayCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PlayerComponent/HealthComponent.h"
#include "Projectile/BallProjectile.h"
#include "PlayerComponent/ProjectileComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/BlueComponent.h"
#include "Map/MyMapBackground.h"
APlayCharacter::APlayCharacter()
{
	IsAnimForbidden = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));
	MapBackground = CreateDefaultSubobject<AMyMapBackground>(TEXT("MapBackground"));

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
void APlayCharacter::RecoverBlueByTick()
{
	if (BlueComponent)
		BlueComponent->RecoverBlueByTick();
}
