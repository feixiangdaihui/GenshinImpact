#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyAnim.h"
#include "PlayerComponent/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

AEnemyCharacter::AEnemyCharacter()
{
    // 启用 Tick
    PrimaryActorTick.bCanEverTick = true;

    // 初始化属性
    CurrentHealth = 100.0f;
    MaxHealth = 100.0f;
    HealHealth = 5.0f;
    AttackPower = 20.0f;
    AttackRange = 100.0f;
	AttackInterval = 2.0f;
    WalkSpeed = 200.0f;
    RunSpeed = 400.0f;
	RotationRate = 540.0f;
	CurrentSpeed = WalkSpeed;
    PatrolRange = 1000.0f;
    DetectionRange = 1000.0f;
	DetectionAngle = 180.0f;
    IsAttacking = false;
    IsBeingAttacked = false;
	IsSitting = false;
	IsPatrol = false;
	IsDead = false;
	SittingTimer = 0.0f;
	PatrolTimer = 0.0f;

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    //获取出生点位置
    SpawnLocation = GetActorLocation();
    // 确保初始健康值不会超过最大值
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

    // 设置初始移动速度
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    // 启动定时器，用于回血
    GetWorld()->GetTimerManager().SetTimer(
        HealTimerHandle,  // 定时器句柄
        this,  // 当前对象
        &AEnemyCharacter::HealOverTime, // 调用当前对象的 HealOverTime 方法
        1.0f,  // 每秒触发一次
        true   // 循环触发
    );
}

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // 处理 Tick 内的逻辑，比如检查是否需要切换移动速度
    if (IsBeingAttacked)
    {

    }
    else if (IsAttacking)
    {

    }
    UpdateMovementSpeed();
}

void AEnemyCharacter::TakeDamage(float DamageAmount)
{
    // 更新生命值
    CurrentHealth -= DamageAmount;

    // 防止生命值小于 0
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

    // 被攻击状态
    IsBeingAttacked = true;

    UE_LOG(LogTemp, Warning, TEXT("Enemy took %f damage, Health now: %f"), DamageAmount, CurrentHealth);

    // 检查是否死亡
    if (CurrentHealth <= 0.0f)
    {
        Die();
    }
    else
    {
        // 一段时间后退出被攻击状态
        GetWorld()->GetTimerManager().SetTimer(
            ResetBeingAttackedTimerHandle,
            [this]() { IsBeingAttacked = false; }, // 退出被攻击状态
            1.0f,  // 1秒后重置
            false  // 不循环触发
        );
    }
}

void AEnemyCharacter::Attack()
{
    if (IsAttacking)
    {
        return; // 如果已经在攻击中，则不重复触发
    }

    IsAttacking = true;

    UE_LOG(LogTemp, Warning, TEXT("Enemy is attacking with %f power!"), AttackPower);

    // 播放攻击动画或执行攻击逻辑
    // 示例：对目标玩家造成伤害（伪代码）
    // if (TargetPlayer)
    // {
    //     TargetPlayer->TakeDamage(AttackPower);
    // }

    // 模拟攻击结束
    GetWorld()->GetTimerManager().SetTimer(
        ResetAttackingTimerHandle,
        [this]() { IsAttacking = false; }, // 退出攻击状态
        AttackInterval,  // 攻击结束后，2秒内不可再次攻击
        false
    );
}

void AEnemyCharacter::Die()
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy has died!"));

	IsDead = true;

    // 移除角色
    Destroy();
}

void AEnemyCharacter::HealOverTime()
{
    if (CurrentHealth < MaxHealth)
    {
        // 增加回血量
        CurrentHealth += HealHealth;

        // 防止超过最大值
        CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

        UE_LOG(LogTemp, Warning, TEXT("Enemy healed for %f, Health now: %f"), HealHealth, CurrentHealth);
    }
}

float AEnemyCharacter::GetAttackRange() const
{
    return AttackRange;
}

FVector AEnemyCharacter::GetSpawnLocation() const
{
    return SpawnLocation;
}

float AEnemyCharacter::GetDetectionRange() const
{
	return DetectionRange;
}

FVector AEnemyCharacter::GetLastDamageDirection() const
{
	return FVector::ZeroVector;
}

void AEnemyCharacter::UpdateMovementSpeed()
{
	// 根据当前速度设置移动速度
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}