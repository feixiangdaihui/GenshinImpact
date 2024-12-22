// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/EquipmentBarComponent.h"
#include "PlayerController/SumPlayerController.h"
#include "Character/PlayCharacter.h"
#include "PlayerComponent/HealthComponent.h"
#include "PlayerComponent/AttackPowerComponent.h"
#include "PlayerComponent/ElementComponent.h"
#include "Item/Equipment/Equipment.h"
#include "Widget/EquipmentBarWidget.h"
#include "Hud/BaseHud.h"
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
	BaseHud = Cast<ABaseHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
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
		
		APlayCharacter* PlayCharacter = Cast<APlayCharacter>(GetOwner());
		if (PlayCharacter)
		{
			//取下原来的装备
			TakeOffEquipment(Equipment->GetEquipmentType());
			//把装备附在角色身上，并设置网格体不可见
			
			Equipment->AttachToActor(PlayCharacter, FAttachmentTransformRules::SnapToTargetIncludingScale);
			Equipment->SetIsHiden(true);
			UE_LOG(LogTemp, Warning, TEXT("WearEquipment"));
			//穿上新的装备
			EquipmentBar[static_cast<int32>(Equipment->GetEquipmentType())] = Equipment;
			//更新属性
			PlayCharacter->HealthComponent->AddMaxHealth(Equipment->GetHealthPower());
			PlayCharacter->AttackPowerComponent->AddAttackPower(Equipment->GetAttackPower());
			PlayCharacter->ElementComponent->AddElementPower(Equipment->GetElementPower());
			//更新UI
			if (BaseHud)
				BaseHud->AddEquipmentBarWidget(PlayCharacter->GetCharacterIndex(), static_cast<int32>(Equipment->GetEquipmentType()), Equipment->GetTexture());
		}
	}
	
}


void UEquipmentBarComponent::TakeOffEquipment(EEquipmentType EquipmentType)
{
	if (EquipmentBar[static_cast<int32>(EquipmentType)] != nullptr)
	{
		APlayCharacter* PlayCharacter = Cast<APlayCharacter>(GetOwner());
		if (PlayCharacter)
		{
			//取下装备
			AEquipment* Equipment = EquipmentBar[static_cast<int32>(EquipmentType)];
			EquipmentBar[static_cast<int32>(EquipmentType)] = nullptr;
			//更新属性
			PlayCharacter->HealthComponent->MinusMaxHealth(Equipment->GetHealthPower());
			PlayCharacter->AttackPowerComponent->MinusAttackPower(Equipment->GetAttackPower());
			PlayCharacter->ElementComponent->MinusElementPower(Equipment->GetElementPower());
			//把装备扔在地上
			//detach,保持原来的大小形状
			Equipment->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			Equipment->SetActorLocation(PlayCharacter->GetActorLocation() + FVector(0, 0, -90));

			Equipment->InitializeData();
			Equipment->SetIsHiden(false);
			//更新UI
			if (BaseHud)
				BaseHud->RemoveEquipmentBarWidget(PlayCharacter->GetCharacterIndex(), static_cast<int32>(EquipmentType));
		}

	}
}

void UEquipmentBarComponent::GetEquipmentBarTextureArray(TArray<TObjectPtr<UTexture2D>>& TextureArray)
{
	TextureArray.SetNum(static_cast<int32>(EEquipmentType_MAX));
	for (int32 i = 0; i < static_cast<int32>(EEquipmentType_MAX); i++)
	{
		if (EquipmentBar[i])
		{
			TextureArray[i] = EquipmentBar[i]->GetTexture();
		}
		else
		{
			TextureArray[i] = nullptr;
		}
	}
}











