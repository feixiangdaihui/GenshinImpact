#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyAnim.h"
#include "EnemyComponent/AttackComponent.h"
#include "EnemyComponent/RemoteAttackComponent.h"
#include "EnemyComponent/SkillAttackComponent.h"
#include "EnemyComponent/MoveComponent.h"
#include "EnemyComponent/ImmobileMoveComponent.h"
#include "EnemyComponent/DetectComponent.h"
#include "EnemyComponent/EnemyHealthComponent.h"
#include "EnemyComponent/ReboundHealthComponent.h"
#include "Interface/AttackInterface.h"
#include "Interface/MoveInterface.h"
#include "Interface/DetectInterface.h"
#include "Interface/EnemyHealthInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GlobalTypes/GlobalTypes.h"

AEnemyCharacter::AEnemyCharacter() : AttackInterface(nullptr), MoveInterface(nullptr), DetectInterface(nullptr), HealthInterface(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	DestroyTime = 2.0f;
	bIsDead = false;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//// 创建组件并绑定到成员变量
	//if (AttackComponentClass)
	//{
	//	AttackComponent = NewObject<UActorComponent>(this, AttackComponentClass);
	//	AttackComponent->RegisterComponent();
	//	AddOwnedComponent(AttackComponent);
	//}
	//if (MoveComponentClass)
	//{
	//	MoveComponent = NewObject<UActorComponent>(this, MoveComponentClass);
	//	MoveComponent->RegisterComponent();
	//	AddOwnedComponent(MoveComponent);
	//}
	//if (DetectComponentClass)
	//{
	//	DetectComponent = NewObject<UActorComponent>(this, DetectComponentClass);
	//	DetectComponent->RegisterComponent();
	//	AddOwnedComponent(DetectComponent);
	//}
	//if (HealthComponentClass)
	//{
	//	HealthComponent = NewObject<UActorComponent>(this, HealthComponentClass);
	//	HealthComponent->RegisterComponent();
	//	AddOwnedComponent(HealthComponent);
	//}
	AttackComponent = FindComponentByClass<UAttackComponent>();
	if (!AttackComponent)AttackComponent = FindComponentByClass<URemoteAttackComponent>();
	if (!AttackComponent)AttackComponent = FindComponentByClass<USkillAttackComponent>();
	MoveComponent = FindComponentByClass<UMoveComponent>();
	if (!MoveComponent)MoveComponent = FindComponentByClass<UImmobileMoveComponent>();
	DetectComponent = FindComponentByClass<UDetectComponent>();
	HealthComponent = FindComponentByClass<UEnemyHealthComponent>();
	if (!HealthComponent)HealthComponent = FindComponentByClass<UReboundHealthComponent>();

	if (!AttackComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create AttackComponent"));
	if (!MoveComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create MoveComponent"));
	if (!HealthComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create HealthComponent"));
	if (!DetectComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create DetectComponent"));

	// 确保接口已初始化
	AttackInterface = Cast<IAttackInterface>(AttackComponent);
	MoveInterface = Cast<IMoveInterface>(MoveComponent);
	DetectInterface = Cast<IDetectInterface>(DetectComponent);
	HealthInterface = Cast<IEnemyHealthInterface>(HealthComponent);

	// 验证接口是否成功初始化
	if (!AttackInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize AttackInterface"));
	}
	if (!MoveInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize MoveInterface"));
	}
	if (!DetectInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize DetectInterface"));
	}
	if (!HealthInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize HealthInterface"));
	}
}


void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bIsDead = HealthInterface->GetIsDead();
}


void AEnemyCharacter::TakeDamageByValue(float DammageValue)
{
	if (HealthInterface)
	{
		HealthInterface->TakeDamageByValue(DammageValue);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in EnemyCharacter!"));
	}
}

void AEnemyCharacter::TakeDamageByPercent(float DammagePercent)
{
	if (HealthInterface)
	{
		HealthInterface->TakeDamageByPercent(DammagePercent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in EnemyCharacter!"));
	}
}

GElement AEnemyCharacter::GetElementType() const
{
	if (HealthInterface)
	{
		return HealthInterface->GetElementType();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in EnemyCharacter!"));
		return GElement::Earth;
	}
}

float AEnemyCharacter::GetLevel() const
{
	if (HealthInterface)
	{
		return HealthInterface->GetLevel();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in EnemyCharacter!"));
		return 10.0f;
	}
}

float AEnemyCharacter::GetCurrentHealthPercent() const
{
	if (HealthInterface)
	{
		return HealthInterface->GetCurrentHealthPercent();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in EnemyCharacter!"));
		return 1.0f;
	}
}

float AEnemyCharacter::GetCurrentShieldPercent() const
{
	if (HealthInterface)
	{
		return HealthInterface->GetCurrentShieldPercent();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthInterface not found in EnemyCharacter!"));
		return 0.0f;
	}
}
