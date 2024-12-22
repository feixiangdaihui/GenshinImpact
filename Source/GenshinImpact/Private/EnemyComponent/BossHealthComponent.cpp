#include "EnemyComponent/BossHealthComponent.h"

// Sets default values for this component's properties
UBossHealthComponent::UBossHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 1000.0f;
	CurrentHealth = MaxHealth;
	HealAmount = 10.0f;
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
