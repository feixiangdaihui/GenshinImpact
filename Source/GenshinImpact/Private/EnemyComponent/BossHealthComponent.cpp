#include "EnemyComponent/BossHealthComponent.h"

// Sets default values for this component's properties
UBossHealthComponent::UBossHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 1000.0f;
	CurrentHealth = MaxHealth;
	HealAmount = 10.0f;
	ShieldHealAmount = 10.0f;
	MaxShield = 1000.0f;
	CurrentShield = MaxShield;
	TimeNeededToHeal = 15.0f;
	TimeSinceLastAttacked = 0.0f;
	bIsDead = false;
	bIsBeingAttacked = false;
	ElementType = GElement::Fire;
}

// Called every frame
void UBossHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bIsBeingAttacked)
	{
		TimeSinceLastAttacked += DeltaTime;
		if (TimeSinceLastAttacked >= TimeNeededToHeal)
		{
			Heal();
			RestoreShield();
			TimeSinceLastAttacked = TimeNeededToHeal;
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

void UBossHealthComponent::TakeDamageByValue(float DamageAmount, float TimeToBeAttacked)
{
	if (bIsDead)
		return;

	if (CurrentShield > 0.0f)
	{
		if (CurrentShield >= DamageAmount)
		{
			CurrentShield -= DamageAmount;
			return;
		}
		else
		{
			DamageAmount -= CurrentShield;
			CurrentShield = 0.0f;
		}
	}

	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy is dead!"));
		CurrentHealth = 0.0f;
		Die();
		return;
	}

	bIsBeingAttacked = true;
	GetWorld()->GetTimerManager().SetTimer(
		BeAttackedStateTimerHandle,
		this,
		&UBossHealthComponent::ResetBeAttacked,
		TimeToBeAttacked,
		false);
}

void UBossHealthComponent::TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked)
{
	if (bIsDead)
		return;

	CurrentHealth -= MaxHealth * DamagePercent;
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		Die();
		return;
	}

	bIsBeingAttacked = true;
	GetWorld()->GetTimerManager().SetTimer(
		BeAttackedStateTimerHandle,
		this,
		&UBossHealthComponent::ResetBeAttacked,
		TimeToBeAttacked,
		false);
}

void UBossHealthComponent::RestoreShield()
{
	if (bIsDead || bIsBeingAttacked || CurrentShield >= MaxShield)
		return;

	CurrentShield += ShieldHealAmount;
	if (CurrentShield >= MaxShield)
		CurrentShield = MaxShield;
}

void UBossHealthComponent::UseSkill(int SkillOpt)
{
	if (bIsDead || bIsBeingAttacked)
		return;

	if (SkillOpt < 0)
		SkillOpt = 0;
	else if (SkillOpt >= Skills.Num())
		SkillOpt = Skills.Num() - 1;

	if (SkillOpt == 0)
	{
		for (int i = 1; i < Skills.Num(); i++)
		{
			if (Skills[i].bCanUse)
			{
				SkillOpt = i;
				break;
			}
		}
	}

	if (SkillOpt == SKILL_RESTORE_SHIELD)
	{
		CurrentShield += Skills[SkillOpt].Damage;
		if (CurrentShield >= MaxShield)
			CurrentShield = MaxShield;
	}
	else if (SkillOpt == SKILL_HEAL)
	{
		CurrentHealth += Skills[SkillOpt].Damage;
		if (CurrentHealth >= MaxHealth)
			CurrentHealth = MaxHealth;
	}

	Skills[SkillOpt].bIsUsing = true;
	Skills[SkillOpt].bCanUse = false;
	GetWorld()->GetTimerManager().SetTimer(
		SkillEndTimerHandle,
		[this, SkillOpt]()
		{
			Skills[SkillOpt].bIsUsing = false;
		},
		Skills[SkillOpt].AnimationDuration,
		false
	);
}

bool UBossHealthComponent::GetIsUsingSkill(int SkillOpt) const
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