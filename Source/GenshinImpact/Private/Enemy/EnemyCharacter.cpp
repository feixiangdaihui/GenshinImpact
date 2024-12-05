#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyAnim.h"
#include "PlayerComponent/HealthComponent.h"
#include "EnemyComponent/AttackComponent.h"
#include "EnemyComponent/MoveComponent.h"
#include "EnemyComponent/DetectComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

AEnemyCharacter::AEnemyCharacter()
{
    // 启用 Tick
    PrimaryActorTick.bCanEverTick = true;

    // 初始化组件
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	MoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	DetectComponent = CreateDefaultSubobject<UDetectComponent>(TEXT("DetectComponent"));
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    
}

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}
