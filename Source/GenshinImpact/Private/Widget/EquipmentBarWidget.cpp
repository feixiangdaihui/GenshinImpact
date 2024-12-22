// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EquipmentBarWidget.h"
#include "Components/Image.h"



void UEquipmentBarWidget::UpdateEquipmentBar(int32 index, UTexture2D* Texture)
{
	if(EquipmentImages.IsValidIndex(index))
	{
		EquipmentImages[index]->SetBrushFromTexture(Texture);
	}
}

void UEquipmentBarWidget::TakeOffEquipment(int32 index)
{
	if (EquipmentImages.IsValidIndex(index))
		EquipmentImages[index]->SetBrushFromTexture(EquipmentBarDefault[index]);
}

void UEquipmentBarWidget::DefaultInitializeEquipmentBar()
{
	EquipmentBarDefault.SetNum(static_cast<int32>(EEquipmentType_MAX));
	EquipmentImages.SetNum(static_cast<int32>(EEquipmentType_MAX));
	for (int index = 0; index < EEquipmentType_MAX; index++)
	{
		EquipmentImages[index] = NewObject<UImage>(this);
		EquipmentImages[index]->SetBrushFromTexture(EquipmentBarDefault[index]);
	}
}
