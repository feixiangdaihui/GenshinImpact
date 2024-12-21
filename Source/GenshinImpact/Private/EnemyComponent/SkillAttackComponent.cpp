#include "EnemyComponent/SkillAttackComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayCharacter.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/HealthComponent.h"

USkillAttackComponent::USkillAttackComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    AttackCooldown = 5.0f;  // 每次攻击的冷却时间
    SkillCooldown = 30.0f;  // 每次技能攻击的冷却时间
    AttackRange = 300.0f;   // 默认攻击范围
    SkillAttackRange = 500.0f;   // 默认技能攻击范围
    AttackDamage = 10.0f;   // 默认攻击伤害
    SkillDamage = 20.0f;   // 默认技能伤害
    bIsAttacking = false;   // 初始状态不在攻击
    bIsSkillAttacking = false;   // 初始状态不在技能攻击
    bCanAttack = true;      // 初始状态可以攻击
    bCanSkillAttack = true;      // 初始状态可以技能攻击
}

void USkillAttackComponent::BeginPlay()
{
    UActorComponent::BeginPlay();
    TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void USkillAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool USkillAttackComponent::CanAttack() const
{
    if (!TargetActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot attack: No target actor!"));
        return false; // 没有目标不能攻击
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot attack: No owner!"));
        return false; // 组件没有绑定到宿主
    }

    FVector OwnerLocation = Owner->GetActorLocation();
    FVector OwnerForward = Owner->GetActorForwardVector();
    FVector TargetLocation = TargetActor->GetActorLocation();

    // 计算与目标的距离
    float DistanceToTarget = FVector::Dist(OwnerLocation, TargetLocation);

    // 距离检查
    if (DistanceToTarget > AttackRange || bIsAttacking || !bCanAttack)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot attack: Target out of range or currently attacking!"));
        return false;
    }

    UE_LOG(LogTemp, Warning, TEXT("Can attack target: %s"), *TargetActor->GetName());
    return true; // 满足所有条件，可以攻击
}

bool USkillAttackComponent::CanSkillAttack() const
{
    if (!TargetActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot skill attack: No target actor!"));
        return false; // 没有目标不能攻击
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot skill attack: No owner!"));
        return false; // 组件没有绑定到宿主
    }

    FVector OwnerLocation = Owner->GetActorLocation();
    FVector OwnerForward = Owner->GetActorForwardVector();
    FVector TargetLocation = TargetActor->GetActorLocation();

    // 计算与目标的距离
    float DistanceToTarget = FVector::Dist(OwnerLocation, TargetLocation);

    // 距离检查
    if (DistanceToTarget > SkillAttackRange || bIsSkillAttacking || !bCanSkillAttack)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot skill attack: Target out of range or currently attacking!"));
        return false;
    }

    UE_LOG(LogTemp, Warning, TEXT("Can skill attack target: %s"), *TargetActor->GetName());
    return true; // 满足所有条件，可以攻击
}

void USkillAttackComponent::NormalAttack()
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
            if (PlayerCharacter && CanAttack())
            {
                PlayerCharacter->HealthComponent->DamageHealthByValue(AttackDamage); // 延迟伤害
            }
            bIsAttacking = false;
        },
        AttackAnimationDuration, // 攻击动画时长
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

void USkillAttackComponent::SkillAttack(int SkillOpt)
{
    switch (SkillOpt)
    {
    case 0://被动触发技能，血量50%以下时触发

        break;
    case 1://主动技能1

        break;
    default:
        break;
    }
}

bool USkillAttackComponent::IsInRange() const
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

bool USkillAttackComponent::IsInSkillRange() const
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
    if (DistanceToTarget <= SkillAttackRange)
        return true;
    else
        return false;
}
