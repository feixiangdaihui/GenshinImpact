#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AEnemyCharacter;

UCLASS()
class GENSHINIMPACT_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AEnemyAIController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
	// 控制的敌人角色
	AEnemyCharacter* EnemyCharacter;

	bool bCanDetectPlayer;
	bool bIsAttacking;
	bool bIsBeingAttacked;
	bool bIsDead;
	bool bIsMoving;
	bool bIsChasing;
	bool bIsResting;

	// 受击状态计时器
	FTimerHandle DestroyTimerHandle;
};
