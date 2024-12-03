// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RealTimeWidget.h"
#include "Components/ProgressBar.h"

void URealTimeWidget::InitializeWidget(float _MaxHealth, float _MaxBlue, float Healthpercent, float Bluepercent)
{
	MaxHealth = _MaxHealth;
	MaxBlue = _MaxBlue;
	CurrentHealth = MaxHealth * Healthpercent;
	CurrentBlue = MaxBlue * Bluepercent;
	HealthBar->SetPercent(Healthpercent);
	BlueBar->SetPercent(Bluepercent);
}
void URealTimeWidget::UpdateHealthBarPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}

void URealTimeWidget::UpdateBlueBarPercent(float BluePercent)
{
	BlueBar->SetPercent(BluePercent);
}
