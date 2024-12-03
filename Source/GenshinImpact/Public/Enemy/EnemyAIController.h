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

    // 检测玩家
    bool DetectPlayer();

    // 巡逻逻辑
    void Patrol();

    // 追击玩家
    void ChasePlayer();

    // 攻击玩家
    void AttackPlayer();

    // 丝滑转向
    void TurnTowards(const FVector& TargetLocation, float DeltaTime, float TurnRate);

protected:
    virtual void BeginPlay() override;

	void UpdateStatePerTick();

public:
    virtual void Tick(float DeltaTime) override;

protected:
    TObjectPtr<APawn> ControlledEnemy;
    TObjectPtr<AActor> TargetPlayer;
    TObjectPtr<AEnemyCharacter> EnemyCharacter;
    FVector PatrolTarget;
    FVector LastKnownPlayerLocation;
};
