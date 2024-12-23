#include "EnemyComponent/SkillAttackComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayCharacter.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/HealthComponent.h"

USkillAttackComponent::USkillAttackComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USkillAttackComponent::BeginPlay()
{
    UActorComponent::BeginPlay();
    TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Skills.Add(FSkill("Occupied", 0.0f, 0.0f, 0.0f, 0.0f));
	Attacks.Add(FAttack("Occupied", 0.0f, 0.0f, 0.0f, 0.0f));
}

void USkillAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	for (int i = 1; i < Skills.Num(); i++)
	{
		if (!Skills[i].bCanUse)
		{
			Skills[i].CurrentCooldown += DeltaTime;
			if (Skills[i].CurrentCooldown >= Skills[i].Cooldown)
			{
				Skills[i].bCanUse = true;
				Skills[i].CurrentCooldown = 0.0f;
			}
		}
	}
}

bool USkillAttackComponent::CanSkillAttack(int SkillOpt) const
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

    if (SkillOpt == 0)
    {
        for (int i = 1; i < Skills.Num(); i++)
        {
            if (Skills[i].Range >= DistanceToTarget && Skills[i].bCanUse && !Skills[i].bIsUsing)
                return true;
        }
        return false;
    }

	if (Skills[SkillOpt].Range >= DistanceToTarget && Skills[SkillOpt].bCanUse && !Skills[SkillOpt].bIsUsing)
		return true;
	else
		return false;
}

void USkillAttackComponent::SkillAttack(int SkillOpt)
{
    if (SkillOpt < 0)
        SkillOpt = 0;
    else if(SkillOpt >= Skills.Num())
		SkillOpt = Skills.Num() - 1;

	if (!CanAttack(SkillOpt))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot skill attack target: %s"), TargetActor ? *TargetActor->GetName() : TEXT("Invalid Target"));
		return;
	}

    if (SkillOpt == 0)
    {
        for (int i = 1; i < Skills.Num(); i++)
            if (CanAttack(i))
                SkillOpt = i;
    }

	Skills[SkillOpt].bIsUsing = true;
    GetWorld()->GetTimerManager().SetTimer(
        SkillEndTimerHandle, // 使用计时器句柄
        [this, SkillOpt]()
        {
            APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
            if (PlayerCharacter && CanSkillAttack(SkillOpt))
                PlayerCharacter->HealthComponent->DamageHealthByValue(Skills[SkillOpt].Damage); // 延迟伤害
            Skills[SkillOpt].bIsUsing = false;
        },
        Skills[SkillOpt].AnimationDuration,
        false
    );

    Skills[SkillOpt].bCanUse = false;
}


bool USkillAttackComponent::IsInSkillRange(int SkillOpt) const
{
    if (SkillOpt < 0)
        SkillOpt = 0;
    else if (SkillOpt >= Skills.Num())
        SkillOpt = Skills.Num() - 1;

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

	if (SkillOpt == 0)
	{
		for (int i = 1; i < Skills.Num(); i++)
		{
			if (Skills[i].Range >= DistanceToTarget)
				return true;
		}
		return false;
	}

	return Skills[SkillOpt].Range >= DistanceToTarget;
}

bool USkillAttackComponent::GetIsSkillAttacking(int SkillOpt) const
{
    if (SkillOpt < 0)
        SkillOpt = 0;
    else if (SkillOpt >= Skills.Num())
        SkillOpt = Skills.Num() - 1;

    if (SkillOpt == 0)
    {
        for (int i = 1; i < Skills.Num(); i++)
        {
            if (Skills[i].bIsUsing)
                return true;
        }
        return false;
    }

    return Skills[SkillOpt].bIsUsing;
}