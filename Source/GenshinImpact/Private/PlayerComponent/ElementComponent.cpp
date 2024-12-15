// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/ElementComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "Character/PlayCharacter.h"
#include "Item/Equipment/Equipment.h"
#include "PlayerComponent/EquipmentBarComponent.h"
// Sets default values for this component's properties
UElementComponent::UElementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UElementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}



