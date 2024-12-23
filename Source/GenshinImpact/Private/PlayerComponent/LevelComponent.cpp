// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/LevelComponent.h"

// Sets default values for this component's properties
ULevelComponent::ULevelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULevelComponent::AddExperience(float ExperienceToAdd)
{
	Experience += ExperienceToAdd;
	while (Experience >= ExperienceToLevelUp)
	{
		LevelUp();
	}
}

void ULevelComponent::LevelUp()
{
	level++;
	Experience -= ExperienceToLevelUp; 
}

