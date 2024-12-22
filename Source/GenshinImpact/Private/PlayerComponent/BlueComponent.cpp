// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/BlueComponent.h"

// Sets default values for this component's properties
UBlueComponent::UBlueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBlueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBlueComponent::RecoverBlueByTick()
{
	AddBlue(BlueRecoverTick);
}

void UBlueComponent::AddBlue(float BlueValue)
{
	CurrentBlue += BlueValue;
	if (CurrentBlue > MaxBlue)
	{
		CurrentBlue = MaxBlue;
	}
}

void UBlueComponent::AddBlueByRate(float Rate)
{
	CurrentBlue += Rate * MaxBlue;
	if (CurrentBlue > MaxBlue)
	{
		CurrentBlue = MaxBlue;
	}
}

bool UBlueComponent::ReduceBlue(float BlueValue)
{
	if (CurrentBlue >= BlueValue)
	{
		CurrentBlue -= BlueValue;
		return true;
	}
	return false;
}

void UBlueComponent::RecoverBlueByValue(float BlueValue)
{
	CurrentBlue += BlueValue;
	if (CurrentBlue > MaxBlue)
	{
		CurrentBlue = MaxBlue;
	}
}

