// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthWidget.generated.h"

class UProgressBar;

UCLASS()
class GENSHINIMPACT_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	float CurrentHealth;

	void InitializeWidget(float _MaxHealth, float Healthpercent = 1.0f);
	void UpdateHealthBarPercent(float HealthPercent);
};
