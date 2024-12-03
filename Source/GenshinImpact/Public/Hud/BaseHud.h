// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHud.generated.h"
class URealTimeWidget;
class ASumPlayerController;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API ABaseHud : public AHUD
{
	GENERATED_BODY()
public:
	ABaseHud();
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<URealTimeWidget> RealTimeWidgetClass;
	UPROPERTY()
	TObjectPtr<URealTimeWidget> RealTimeWidget;
	UPROPERTY()
	TObjectPtr<ASumPlayerController> PlayerController;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void InitializeHud();
	void UpdateHud();
	void UpdateRealTimeWidget();
};
