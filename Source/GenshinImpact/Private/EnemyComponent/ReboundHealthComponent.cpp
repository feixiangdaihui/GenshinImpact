#include "EnemyComponent/ReboundHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Character/PlayCharacter.h"
#include "PlayerController/SumPlayerController.h"
#include "PlayerComponent/HealthComponent.h"

UReboundHealthComponent::UReboundHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 1000.0f;
	CurrentHealth = MaxHealth;
	HealAmount = 10.0f;
	TimeNeededToHeal = 15.0f;
	TimeSinceLastAttacked = 0.0f;
	bIsDead = false;
	bIsBeingAttacked = false;
	ReboundRatio = 0.02f;
	ElementType = GElement::Fire;
	Level = 10.0f;
}

void UReboundHealthComponent::TakeDamageByValue(float DamageAmount, float TimeToBeAttacked)
{
	if (bIsDead)
		return;

	CurrentHealth -= DamageAmount;
	APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	PlayerCharacter->HealthComponent->DamageHealthByValue(DamageAmount * ReboundRatio);
	UE_LOG(LogTemp, Warning, TEXT("player :%s"), *PlayerCharacter->GetName());
	UE_LOG(LogTemp, Warning, TEXT("ReboundRatio :%f"), ReboundRatio);
	UE_LOG(LogTemp, Warning, TEXT("rebound :%f"), DamageAmount * ReboundRatio);
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
		&UReboundHealthComponent::ResetBeAttacked,
		TimeToBeAttacked,
		false);
}

void UReboundHealthComponent::TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked)
{
	if (bIsDead)
		return;

	CurrentHealth -= MaxHealth * DamagePercent;
	APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	UE_LOG(LogTemp, Warning, TEXT("player :%s"), *PlayerCharacter->GetName());
	PlayerCharacter->HealthComponent->DamageHealthByRate(DamagePercent * ReboundRatio);
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
		&UReboundHealthComponent::ResetBeAttacked,
		TimeToBeAttacked,
		false);
}