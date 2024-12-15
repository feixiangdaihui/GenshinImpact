// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RealTimeWidget.h"
#include "Components/ProgressBar.h"

void URealTimeWidget::UpdateWidget(float _MaxHealth, float _CurrentHealth, float _MaxBlue, float _CurrentBlue)
{
	MaxHealth = _MaxHealth;
	MaxBlue = _MaxBlue;
	CurrentHealth = _CurrentHealth;
	CurrentBlue = _CurrentBlue;
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
	BlueBar->SetPercent(CurrentBlue / MaxBlue);
}

