#include "EnemyComponent/AttackComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayCharacter.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/HealthComponent.h"

UAttackComponent::UAttackComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // 默认属性值
    AttackCooldown = 2.0f;  // 每次攻击的冷却时间
    AttackRange = 200.0f;   // 默认攻击范围
	AttackDamage = 10.0f;   // 默认攻击伤害
    bIsAttacking = false;   // 初始状态不在攻击
    bCanAttack = true;      // 初始状态可以攻击
}

void UAttackComponent::BeginPlay()
{
    UActorComponent::BeginPlay();
    // 获取攻击对象
    TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

bool UAttackComponent::CanAttack() const
{
    if (!TargetActor)
    {
        return false; // 没有目标不能攻击
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return false; // 组件没有绑定到宿主
    }

    // 计算与目标的距离
    float DistanceToTarget = FVector::Dist(Owner->GetActorLocation(), TargetActor->GetActorLocation());

    // 检查距离是否在攻击范围内
    if (DistanceToTarget <= AttackRange && !bIsAttacking && bCanAttack)
    {
		UE_LOG(LogTemp, Warning, TEXT("Can attack target: %s"), *TargetActor->GetName());
        return true;
    }
    else
		return false;
}

bool UAttackComponent::IsInRange() const
{
	if (!TargetActor)
	{
		return false; // 没有目标不能攻击
	}
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return false; // 组件没有绑定到宿主
	}
	// 计算与目标的距离
	float DistanceToTarget = FVector::Dist(Owner->GetActorLocation(), TargetActor->GetActorLocation());
	// 检查距离是否在攻击范围内
	if (DistanceToTarget <= AttackRange)
		return true;
	else
		return false;
}

void UAttackComponent::NormalAttack()
{
    if (!CanAttack())
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot attack target: %s"), TargetActor ? *TargetActor->GetName() : TEXT("Invalid Target"));
        return;
    }

    // 执行攻击逻辑
    UE_LOG(LogTemp, Warning, TEXT("Performing attack on target: %s"), *TargetActor->GetName());

    // 对目标造成伤害
    bIsAttacking = true;

    GetWorld()->GetTimerManager().SetTimer(
        AttackEndTimerHandle, // 使用计时器句柄
        [this]() {
            APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
            if (PlayerCharacter)
            {
                PlayerCharacter->HealthComponent->DamageHealthByValue(AttackDamage); // 延迟伤害
            }
            bIsAttacking = false;
        },
        0.6f, // 假设动画持续时间为0.6秒，可以根据实际动画调整
        false
    );

    // 攻击完成后进入冷却
	bCanAttack = false;

    // 使用计时器重置攻击状态
    GetWorld()->GetTimerManager().SetTimer(
        AttackCooldownTimerHandle, // 使用计时器句柄
        [this]() { ResetAttackCooldown(); }, // Lambda 函数，用于重置攻击状态
        AttackCooldown,
        false
    );
}

void UAttackComponent::ResetAttackCooldown()
{
	bCanAttack = true;
    UE_LOG(LogTemp, Warning, TEXT("Attack cooldown reset."));
}
