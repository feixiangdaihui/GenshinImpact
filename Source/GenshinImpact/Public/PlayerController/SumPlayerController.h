// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SumPlayerController.generated.h"

/**
 * 
 */
class ABaseHud;
UCLASS()
class GENSHINIMPACT_API ASumPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void UpdateHud();
	TObjectPtr<ABaseHud> Hud;
	virtual void BeginPlay() override;
	void ChangeCharacter();
	
};
