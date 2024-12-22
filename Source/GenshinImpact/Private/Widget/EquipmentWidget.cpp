// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EquipmentWidget.h"

void UEquipmentWidget::SetTextRotation(FVector Rotation)
{
	//3d转成2d，只要xy轴
	FVector2D Rotation2D(Rotation.X, Rotation.Y);

	// 设置文本的旋转
	if (TextBlockTips)
	{
		TextBlockTips->SetRenderTransformPivot(Rotation2D);
	}
}

void UEquipmentWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	TextBlockTips->SetVisibility(InVisibility);
}
