// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnemyHealthWidget.h"
#include "Components/ProgressBar.h"

void UEnemyHealthWidget::InitializeWidget(float _MaxHealth, float Healthpercent)
{
	MaxHealth = _MaxHealth;
	CurrentHealth = MaxHealth * Healthpercent;
	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	HealthBar->SetPercent(Healthpercent);
}

void UEnemyHealthWidget::UpdateHealthBarPercent(float HealthPercent)
{
	if(HealthBar)
		HealthBar->SetPercent(HealthPercent);
	else  
		UE_LOG(LogTemp, Error, TEXT("HealthBar not found in EnemyHealthWidget!"));	
}