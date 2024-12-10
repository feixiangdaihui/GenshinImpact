#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyAnim.h"
#include "EnemyComponent/AttackComponent.h"
#include "EnemyComponent/MoveComponent.h"
#include "EnemyComponent/DetectComponent.h"
#include "EnemyComponent/EnemyHealthComponent.h"
#include "Interface/AttackInterface.h"
#include "Interface/MoveInterface.h"
#include "Interface/DetectInterface.h"
#include "Interface/EnemyHealthInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GlobalTypes/GlobalTypes.h"

AEnemyCharacter::AEnemyCharacter() : AttackInterface(nullptr), MoveInterface(nullptr), DetectInterface(nullptr), HealthInterface(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;

    // 创建组件并绑定到成员变量
    AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
    MoveComponent   = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
    DetectComponent = CreateDefaultSubobject<UDetectComponent>(TEXT("DetectComponent"));
    HealthComponent = CreateDefaultSubobject<UEnemyHealthComponent>(TEXT("HealthComponent"));
	if (!AttackComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create AttackComponent"));
	if (!MoveComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create MoveComponent"));
	if (!HealthComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create HealthComponent"));
	if (!DetectComponent)
		UE_LOG(LogTemp, Error, TEXT("Failed to create DetectComponent"));

    // 将组件添加到角色中
    AddOwnedComponent(AttackComponent);
    AddOwnedComponent(MoveComponent);
    AddOwnedComponent(DetectComponent);
    AddOwnedComponent(HealthComponent);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

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
}


void AEnemyCharacter::TakeDammageByValue(float DammageValue)
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

void AEnemyCharacter::TakeDammageByPercent(float DammagePercent)
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

GElement AEnemyCharacter::GetElement()
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

