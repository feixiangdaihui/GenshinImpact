#include "Character/PlayCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PlayerComponent/HealthComponent.h"
#include "Projectile/BallProjectile.h"
#include "PlayerComponent/ProjectileComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/BlueComponent.h"
#include "Map/MyMapBackground.h"
#include "PlayerComponent/ElementComponent.h"
#include "PlayerComponent/AttackPowerComponent.h"

APlayCharacter::APlayCharacter()
{
	IsAnimForbidden = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	BlueComponent = CreateDefaultSubobject<UBlueComponent>(TEXT("BlueComponent"));
	MapBackground = CreateDefaultSubobject<AMyMapBackground>(TEXT("MapBackground"));
	EquipmentBarComponent = CreateDefaultSubobject<UEquipmentBarComponent>(TEXT("EquipmentBarComponent"));
	ElementComponent = CreateDefaultSubobject<UElementComponent>(TEXT("ElementComponent"));
	AttackPowerComponent = CreateDefaultSubobject<UAttackPowerComponent>(TEXT("AttackPowerComponent"));

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

