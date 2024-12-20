// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BaseHud.h"
#include"Widget/RealTimeWidget.h"
#include"Character/PlayCharacter.h"
#include"Components/ProgressBar.h"
#include"PlayerComponent/HealthComponent.h"
#include"PlayerController/SumPlayerController.h"
#include"PlayerComponent/BlueComponent.h"
ABaseHud::ABaseHud()
{
	PrimaryActorTick.bCanEverTick = true;
	

}
void ABaseHud::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ASumPlayerController>(GetOwningPlayerController());
	if (PlayerController)
	{
		Characters = PlayerController->Characters;
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
