#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/MoveInterface.h"
#include "MoveComponent.generated.h"

/**
 * 移动组件，负责实现移动逻辑
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API UMoveComponent : public UActorComponent, public IMoveInterface
{
    GENERATED_BODY()

public:
    // 构造函数
    UMoveComponent();

    // 实现接口中的方法
    virtual void MoveTo(const FVector& Location) override;
    virtual void Patrol() override;
    virtual void ChasePlayer() override;
    virtual void TurnTo(const FVector& TargetLocation, float DeltaTime, float TurnRate) override;

protected:
    virtual void BeginPlay() override;

protected:
    // 出生点位置
    FVector SpawnLocation;

    // 巡逻点范围
    UPROPERTY(EditAnywhere, Category = "Move Settings")
    float PatrolRange;

    // 当前速度
    float CurrentSpeed;

    // 走路速度
    UPROPERTY(EditAnywhere, Category = "Move Settings")
    float WalkSpeed;

    // 跑步速度
    UPROPERTY(EditAnywhere, Category = "Move Settings")
    float RunSpeed;

    // 转向速度
    UPROPERTY(EditAnywhere, Category = "Move Settings")
    float TurnRate;

	// 是否正在移动
    bool bIsMoving;

	// 是否正在追击
	bool bIsChasing;

	// 是否正在休息
	bool bIsResting;
};
