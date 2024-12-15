// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RealTimeWidget.generated.h"
class UProgressBar;

/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API URealTimeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* BlueBar;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float MaxBlue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	float CurrentBlue;
	void UpdateWidget(float _MaxHealth, float _CurrentHealth, float _MaxBlue, float _CurrentBlue);



	
};
