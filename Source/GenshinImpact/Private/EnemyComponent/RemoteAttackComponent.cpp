#include "EnemyComponent/RemoteAttackComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayCharacter.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/HealthComponent.h"

URemoteAttackComponent::URemoteAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	RemoteAttackCooldown = 5.0f;  // 每次攻击的冷却时间
	RemoteAttackRange = 1000.0f;   // 默认攻击范围
	RemoteAttackDamage = 10.0f;   // 默认攻击伤害
	bIsRemoteAttacking = false;   // 初始状态不在攻击
	bCanRemoteAttack = true;      // 初始状态可以攻击
}

void URemoteAttackComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
	TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void URemoteAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool URemoteAttackComponent::CanRemoteAttack() const
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
	if (DistanceToTarget <= RemoteAttackRange && !bIsRemoteAttacking && bCanRemoteAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can remote attack target: %s"), *TargetActor->GetName());
		return true;
	}
	else
		return false;
}

bool URemoteAttackComponent::IsInRemoteRange() const
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
	if (DistanceToTarget <= RemoteAttackRange)
	{
		return true;
	}
	else
		return false;
}

void URemoteAttackComponent::NormalRemoteAttack()
{
	if (!CanAttack())
	{
		return;
	}
	// 攻击逻辑
	UE_LOG(LogTemp, Warning, TEXT("Remote attack!"));
	// 设置攻击状态
	bIsRemoteAttacking = true;
	bCanRemoteAttack = false;

	FVector PlayerLocation = TargetActor->GetActorLocation();

	// 重置攻击状态
	GetWorld()->GetTimerManager().SetTimer(
		RemoteAttackEndTimerHandle,
		this,
		&URemoteAttackComponent::ResetRemoteAttackCooldown,
		RemoteAttackAnimationDuration,
		false);
}

void URemoteAttackComponent::ResetRemoteAttackCooldown()
{
	bCanRemoteAttack = true;
	bIsRemoteAttacking = false;
	UE_LOG(LogTemp, Warning, TEXT("Attack cooldown reset."));
}

