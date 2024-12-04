// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/AttackPowerComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "Character/PlayCharacter.h"
#include "PlayerComponent/EquipmentBarComponent.h"

// Sets default values for this component's properties
UAttackPowerComponent::UAttackPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackPowerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackPowerComponent::UpdateAttackPower()
{
	ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(PlayerController->GetCharacter());
		if (PlayerCharacter)
		{
			SumAttackPower = BaseAttackPower;
			for (auto Equipment : PlayerCharacter->EquipmentBarComponent->EquipmentBar)
			{
				if (Equipment)
				{
					SumAttackPower += Equipment->AttackPower;
				}
			}
		}
	}

}

