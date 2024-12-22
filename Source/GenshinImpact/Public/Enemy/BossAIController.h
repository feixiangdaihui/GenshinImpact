// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy/EnemyAIController.h"
#include "BossAIController.generated.h"

UCLASS()
class GENSHINIMPACT_API ABossAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:
	ABossAIController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
