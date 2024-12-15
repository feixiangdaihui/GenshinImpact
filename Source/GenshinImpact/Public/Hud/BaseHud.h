// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHud.generated.h"
class URealTimeWidget;
class ASumPlayerController;
class APlayCharacter;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API ABaseHud : public AHUD
{
	GENERATED_BODY()
public:
	ABaseHud();
	//RealTimeWidget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TArray<TSubclassOf<URealTimeWidget>> RealTimeWidgetClasses;



	UPROPERTY()
	TObjectPtr<ASumPlayerController> PlayerController;
	TArray<TObjectPtr<APlayCharacter>> Characters;

	TArray<TObjectPtr<URealTimeWidget>> RealTimeWidgets;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void UpdateRealTimeWidget();
};
