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
	if (RealTimeWidgetClass)
	{
		RealTimeWidget = CreateWidget<URealTimeWidget>(GetWorld(), RealTimeWidgetClass);
		RealTimeWidget->AddToViewport();
	}
	InitializeHud();
}

void ABaseHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateHud();
}

void ABaseHud::InitializeHud()
{
	if (RealTimeWidgetClass && PlayerController)
	{
		APlayCharacter* Player = Cast<APlayCharacter>(PlayerController->GetPawn());
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("InitializeHud"));
			UHealthComponent* HealthComponent = Player->HealthComponent;
			if (HealthComponent)
			{
				UE_LOG(LogTemp, Warning, TEXT("InitializeWidget"));
				RealTimeWidget->InitializeWidget(HealthComponent->MaxHealth, 100.0f, HealthComponent->RemainHealthRate, 1.0f);
			}
		}
	}
}

void ABaseHud::UpdateHud()
{
	UpdateRealTimeWidget();
}

void ABaseHud::UpdateRealTimeWidget()
{
	if (RealTimeWidgetClass && PlayerController)
	{
		APlayCharacter* Player = Cast<APlayCharacter>(PlayerController->GetPawn());
		if (Player)
		{
			UHealthComponent* HealthComponent = Player->HealthComponent;
			UBlueComponent* BlueComponent = Player->BlueComponent;
			if (HealthComponent)
			{
				RealTimeWidget->CurrentHealth = HealthComponent->CurrentHealth;
				RealTimeWidget->MaxHealth = HealthComponent->MaxHealth;
				RealTimeWidget->UpdateHealthBarPercent(HealthComponent->RemainHealthRate);

			}
			if (BlueComponent)
			{
				//打印蓝量
				RealTimeWidget->CurrentBlue = BlueComponent->CurrentBlue;
				RealTimeWidget->MaxBlue = BlueComponent->MaxBlue;
				RealTimeWidget->UpdateBlueBarPercent(BlueComponent->CurrentBlue / BlueComponent->MaxBlue);

			}
		}
	}
}
