// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SumPlayerController.h"
#include "Hud/BaseHud.h"
void ASumPlayerController::UpdateHud()
{
	if (Hud)
	{
		Hud->UpdateHud();
	}
}

void ASumPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Hud = Cast<ABaseHud>(GetHUD());


}

void ASumPlayerController::ChangeCharacter()
{

}
