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
#include"GameSave/MyGameInstance.h"

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
	RecoverBlueByTick();

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
		EnhancedInputComponent->BindAction(ChangeCharacterAction, ETriggerEvent::Started, this, &APlayCharacter::SeqChangeCharacter);
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
		EquipmentBarComponent->UpdateAttribute();
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


void APlayCharacter::LoadCharacterData(FCharacterData& InitData)
{
	
	HealthComponent->InitializeHealthComponent(InitData.CurrentHealth);
	BlueComponent->InitializeBlueComponent(InitData.CurrentBlue);
	LevelComponent->InitializeLevelComponent(InitData.CurrentLevel, InitData.CurrentExperience);
	for (int i = 0; i < InitData.EquipmentBarClass.Num(); i++)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		AEquipment* Equipment = GetWorld()->SpawnActor<AEquipment>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
		Equipment->SetEquipmentType(static_cast<EEquipmentType>(i));
		EquipmentBarComponent->WearEquipment(Equipment);
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
			CharacterData.EquipmentBarClass.Add(Equipment->GetClass()->GetName());
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
		EquipmentBarComponent->UpdateAttribute();
	}
}

inline int APlayCharacter::GetLevel() const
{
	return LevelComponent->GetCurrentLevel();
}

