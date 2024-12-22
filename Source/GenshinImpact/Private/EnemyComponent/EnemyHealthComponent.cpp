#include "EnemyComponent/EnemyHealthComponent.h"

// Sets default values for this component's properties
UEnemyHealthComponent::UEnemyHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 1000.0f;
	CurrentHealth = MaxHealth;
	HealAmount = 10.0f;
	TimeNeededToHeal = 15.0f;
	TimeSinceLastAttacked = 0.0f;
	bIsDead = false;
	bIsBeingAttacked = false;
	ElementType = GElement::Fire;
	Level = 10.0f;
}

// Called when the game starts
void UEnemyHealthComponent::BeginPlay()
{
	UActorComponent::BeginPlay();
}

// Called every frame
void UEnemyHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bIsBeingAttacked)
	{
		TimeSinceLastAttacked += DeltaTime;
		if (TimeSinceLastAttacked >= TimeNeededToHeal)
		{
			Heal();
			TimeSinceLastAttacked = TimeNeededToHeal;
		}
	}
}

void UEnemyHealthComponent::TakeDamageByValue(float DamageAmount, float TimeToBeAttacked)
{
	if (bIsDead)
		return;

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
		&UEnemyHealthComponent::ResetBeAttacked,
		TimeToBeAttacked,
		false);
}

void UEnemyHealthComponent::TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked)
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
		&UEnemyHealthComponent::ResetBeAttacked,
		TimeToBeAttacked, 
		false);
}

void UEnemyHealthComponent::Die()
{
	bIsBeingAttacked = false;
	bIsDead = true;
	CurrentHealth = 0.0f;
	UE_LOG(LogTemp, Warning, TEXT("bIsDead: %s"), bIsDead ? TEXT("true") : TEXT("false"));

}

void UEnemyHealthComponent::Heal()
{
	if (bIsDead || bIsBeingAttacked || CurrentHealth >= MaxHealth)
		return;

	CurrentHealth += HealAmount;
	if (CurrentHealth >= MaxHealth)
		CurrentHealth = MaxHealth;
}

