#include "EnemyComponent/AttackComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayCharacter.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/HealthComponent.h"
#include "GlobalTypes/GlobalTypes.h"

UAttackComponent::UAttackComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
	TargetActor = nullptr;  // 初始状态没有攻击对象
}

void UAttackComponent::BeginPlay()
{
    UActorComponent::BeginPlay();
    // 获取攻击对象
    TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);


    UE_LOG(LogTemp, Warning, TEXT("Number of Attacks: %d"), Attacks.Num());

}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
    static bool FirstFrame = true;
	if (FirstFrame)
	{
		FirstFrame = false;
		TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}
	for (int i = 1; i < Attacks.Num(); i++)
	{
		if (!Attacks[i].bCanUse)
		{
			Attacks[i].CurrentCooldown += DeltaTime;
			if (Attacks[i].CurrentCooldown >= Attacks[i].Cooldown)
			{
				Attacks[i].bCanUse = true;
				Attacks[i].CurrentCooldown = 0.0f;
			}
		}
	}
}

bool UAttackComponent::CanAttack(int AttackOpt) const
{
    if (AttackOpt < 0)
        AttackOpt = 0;
    else if (AttackOpt >= Attacks.Num())
        AttackOpt = Attacks.Num() - 1;

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

    if (AttackOpt == 0)
    {
		UE_LOG(LogTemp, Warning, TEXT("atkcop: attackopt is %d"), Attacks.Num());
		for (int i = 1; i < Attacks.Num(); i++)
		{
            if (DistanceToTarget <= Attacks[i].Range && !Attacks[i].bIsUsing && Attacks[i].bCanUse)
            {
				UE_LOG(LogTemp, Warning, TEXT("atkcop: exist can attack target"));
                return true;
            }
            else 
                UE_LOG(LogTemp, Warning, TEXT("atkcop: %d %d %d %d"), i, DistanceToTarget <= Attacks[i].Range, Attacks[i].bIsUsing, Attacks[i].bCanUse);
		}
        UE_LOG(LogTemp, Warning, TEXT("atkcop: all annot attack target"));
        return false;
    }

    // 检查距离是否在攻击范围内
    if (DistanceToTarget <= Attacks[AttackOpt].Range && !Attacks[AttackOpt].bIsUsing && Attacks[AttackOpt].bCanUse)
    {
		UE_LOG(LogTemp, Warning, TEXT("atkcop: can attack target"));
		return true;
    }
    else
    {
		UE_LOG(LogTemp, Warning, TEXT("atkcop: cannot attack target"));
		return false;
    }
		
}

bool UAttackComponent::IsInRange(int AttackOpt) const
{
    if (AttackOpt < 0)
        AttackOpt = 0;
    else if (AttackOpt >= Attacks.Num())
        AttackOpt = Attacks.Num() - 1;

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

    if (AttackOpt == 0)
    {
        for (int i = 1; i < Attacks.Num(); i++)
        {
            if (DistanceToTarget <= Attacks[i].Range)
                return true;
        }
        return false;
    }

	// 检查距离是否在攻击范围内
	if (DistanceToTarget <= Attacks[AttackOpt].Range)
		return true;
	else
		return false;
}

bool UAttackComponent::GetIsAttacking(int AttackOpt) const
{
    if (AttackOpt < 0)
        AttackOpt = 0;
    else if (AttackOpt >= Attacks.Num())
        AttackOpt = Attacks.Num() - 1;

	if (AttackOpt == 0)
	{
		for (int i = 1; i < Attacks.Num(); i++)
			if (Attacks[i].bIsUsing)
				return true;
		return false;
	}

	return Attacks[AttackOpt].bIsUsing;
}

void UAttackComponent::NormalAttack(int AttackOpt)
{
    if (AttackOpt < 0)
        AttackOpt = 0;
    else if (AttackOpt >= Attacks.Num())
        AttackOpt = Attacks.Num() - 1;

    if (!CanAttack(AttackOpt))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot attack target: %s"), TargetActor ? *TargetActor->GetName() : TEXT("Invalid Target"));
        return;
    }

    // 执行攻击逻辑
    UE_LOG(LogTemp, Warning, TEXT("Performing attack on target: %s"), *TargetActor->GetName());

    if (AttackOpt == 0)
    {
        for (int i = 1; i < Attacks.Num(); i++)
            if (CanAttack(i))
            {
                AttackOpt = i;
                break;
            }
    }

    // 对目标造成伤害
    Attacks[AttackOpt].bIsUsing = true;

    GetWorld()->GetTimerManager().SetTimer(
        AttackEndTimerHandle, // 使用计时器句柄
        [this, AttackOpt]()
        {
            APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
            if (PlayerCharacter)
                PlayerCharacter->HealthComponent->DamageHealthByValue(Attacks[AttackOpt].Damage); // 延迟伤害
			Attacks[AttackOpt].bIsUsing = false;
        },
        Attacks[AttackOpt].AnimationDuration,
        false
    );

    // 攻击完成后进入冷却
	Attacks[AttackOpt].bCanUse = false;
}
