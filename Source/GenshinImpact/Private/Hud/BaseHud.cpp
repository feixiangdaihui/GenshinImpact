// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include"Widget/RealTimeWidget.h"
#include"Character/PlayCharacter.h"
#include"Components/ProgressBar.h"
#include"PlayerComponent/HealthComponent.h"
#include"PlayerController/SumPlayerController.h"
#include"PlayerComponent/BlueComponent.h"
#include"Widget/EquipmentBarWidget.h"
ABaseHud::ABaseHud()
{
	PrimaryActorTick.bCanEverTick = true;
	

}
void ABaseHud::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ASumPlayerController>(GetOwningPlayerController());
	CurrentCharacterIndex = PlayerController->GetCurrentCharacterIndex();
	if (PlayerController)
	{
		Characters = PlayerController->Characters;
	}
	if (EquipmentBarWidgetClass)
	{
		for (int i = 0; i < Characters.Num(); i++)
		{
			TObjectPtr<UEquipmentBarWidget> NewEquipmentBarWidget = CreateWidget<UEquipmentBarWidget>(GetWorld(), EquipmentBarWidgetClass);
			EquipmentBarWidget.Add(NewEquipmentBarWidget);
			NewEquipmentBarWidget->DefaultInitializeEquipmentBar();
		}
		EquipmentBarWidget[CurrentCharacterIndex]->AddToViewport();
	}
	for (int i = 0; i < RealTimeWidgetClasses.Num(); i++)
	{
		if (RealTimeWidgetClasses[i])
		{
			URealTimeWidget* Widget = CreateWidget<URealTimeWidget>(GetWorld(), RealTimeWidgetClasses[i]);
			if (Widget)
			{
				RealTimeWidgets.Add(Widget);
				Widget->AddToViewport();
			}
		}
	}
	LoadEquipmentBarWidget();
}

void ABaseHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateRealTimeWidget();
}




void ABaseHud::UpdateRealTimeWidget()
{
	for (int i = 0; i < Characters.Num(); i++)
	{
		if (Characters[i])
		{
			if (RealTimeWidgets[i])
			{
				RealTimeWidgets[i]->UpdateWidget(Characters[i]->HealthComponent->GetMaxHealth(), Characters[i]->HealthComponent->GetCurrentHealth(), Characters[i]->BlueComponent->GetMaxBlue(), Characters[i]->BlueComponent->GetCurrentBlue());
			}
		}
	}
}

void ABaseHud::AddEquipmentBarWidget(int32 CharacterIndex, int32 index, UTexture2D* Texture)
{
	if (EquipmentBarWidget.IsValidIndex(CharacterIndex) && EquipmentBarWidget[CharacterIndex])
	{
		EquipmentBarWidget[CharacterIndex]->UpdateEquipmentBar(index, Texture);
	}
}

void ABaseHud::RemoveEquipmentBarWidget(int32 CharacterIndex, int32 index)
{
	if (EquipmentBarWidget.IsValidIndex(CharacterIndex) && EquipmentBarWidget[CharacterIndex])
	{
		EquipmentBarWidget[CharacterIndex]->TakeOffEquipment(index);
	}
}

void ABaseHud::ChangeCharacterUI()
{
	if (EquipmentBarWidget.IsValidIndex(CurrentCharacterIndex))
	{
		EquipmentBarWidget[CurrentCharacterIndex]->RemoveFromParent();
	}
	CurrentCharacterIndex = PlayerController->GetCurrentCharacterIndex();
	if (EquipmentBarWidget.IsValidIndex(CurrentCharacterIndex))
	{
		EquipmentBarWidget[CurrentCharacterIndex]->AddToViewport();
	}
}

void ABaseHud::LoadEquipmentBarWidget()
{
	for (auto NewCharater : Characters)
	{
		if (NewCharater)
		{
			TArray<TObjectPtr<UTexture2D>> TextureArray;
			NewCharater->EquipmentBarComponent->GetEquipmentBarTextureArray(TextureArray);
			for (int i = 0; i < TextureArray.Num(); i++)
			{
				if (TextureArray[i])
				{
					AddEquipmentBarWidget(NewCharater->GetCharacterIndex(), i, TextureArray[i]);
				}
			}
		}
	}
}





