// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthComponent::DamageHealthByValue(float DamageValue)
{
	CurrentHealth -= DamageValue;
	RemainHealthRate = CurrentHealth / MaxHealth;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		RemainHealthRate = 0;
	}
}

void UHealthComponent::DamageHealthByRate(float DamageRate)
{
	CurrentHealth -= MaxHealth * DamageRate;
	RemainHealthRate = CurrentHealth / MaxHealth;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		RemainHealthRate = 0;
	}
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

