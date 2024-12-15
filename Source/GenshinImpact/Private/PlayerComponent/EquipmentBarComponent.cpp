// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/EquipmentBarComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "Character/PlayCharacter.h"
#include "PlayerComponent/HealthComponent.h"
#include "PlayerComponent/AttackPowerComponent.h"
#include "PlayerComponent/ElementComponent.h"

// Sets default values for this component's properties
UEquipmentBarComponent::UEquipmentBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	EquipmentBar.SetNum(static_cast<int32>(EEquipmentType_MAX));
	// ...
}


// Called when the game starts
void UEquipmentBarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UEquipmentBarComponent::WearEquipment(AEquipment* Equipment)
{
	if (Equipment)
	{
		if (EquipmentBar[static_cast<int32>(Equipment->GetEquipmentType())] != nullptr)
		{
			//放入背包
			UE_LOG(LogTemp, Warning, TEXT("EquipmentBarComponent: WearEquipment: %s"), *Equipment->GetName());
		}
		EquipmentBar[static_cast<int32>(Equipment->GetEquipmentType())] = Equipment;
	}
	
}


void UEquipmentBarComponent::TakeOffEquipment(EEquipmentType& EquipmentType)
{
	if (EquipmentBar[static_cast<int32>(EquipmentType)] != nullptr)
	{
		//放入背包
		UE_LOG(LogTemp, Warning, TEXT("EquipmentBarComponent: TakeOffEquipment: %s"), *EquipmentBar[static_cast<int32>(EquipmentType)]->GetName());
		EquipmentBar[static_cast<int32>(EquipmentType)] = nullptr;
	}
}

void UEquipmentBarComponent::UpdateAttribute()
{
	ASumPlayerController* PlayerController = Cast<ASumPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		APlayCharacter* PlayerCharacter = Cast<APlayCharacter>(PlayerController->GetCharacter());
		if (PlayerCharacter)
		{
			float NewMaxHealth = 0.0f, NewElementPower = 0.0f, NewAttackPower = 0.0f;
			for (auto Equipment : PlayerCharacter->EquipmentBarComponent->EquipmentBar)
			{
				if (Equipment)
				{
					NewMaxHealth += Equipment->HealthPower;
					NewElementPower += Equipment->ElementPower;
					NewAttackPower += Equipment->AttackPower;
				}
			}
			PlayerCharacter->HealthComponent->UpdateMaxHealthByAdd(NewMaxHealth);
			PlayerCharacter->ElementComponent->UpdateSumElementPowerByAdd(NewElementPower);
			PlayerCharacter->AttackPowerComponent->UpdateSumAttackPowerByAdd(NewAttackPower);
		}
	}
}





