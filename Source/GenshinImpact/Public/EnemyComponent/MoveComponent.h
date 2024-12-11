#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/MoveInterface.h"
#include "MoveComponent.generated.h"

class UCharacterMovementComponent;

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
    virtual void MoveTo(const FVector& Location, float AcceptRadius) override;
    virtual void MoveTo(const FVector& Location, float AcceptRadius, float Speed);
    virtual void Patrol() override;
    virtual void ChasePlayer() override;
    virtual void TurnTo(const FVector& TargetLocation, float deltaTime) override;
	virtual void Stop() override;
	virtual bool GetIsMoving() const override { return bIsMoving; }
	virtual bool GetIsChasing() const override { return bIsChasing; }
	virtual bool GetIsResting() const override { return bIsResting; }
    virtual bool GetIsIdling() const override { return bIsIdling; }
	virtual FVector GetSpawnLocation() const { return SpawnLocation; }

protected:
    virtual void BeginPlay() override;

    void StopResting() { bIsResting = false; };
    void StartResting() { bIsResting = true, PatrolTarget = FVector::ZeroVector; };

protected:
    // 出生点位置
    FVector SpawnLocation;

	// 巡逻目标点
	FVector PatrolTarget;

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

    // 巡逻时间
	UPROPERTY(EditAnywhere, Category = "Move Settings")
	float PatrolTime;

    // 休息时间
	UPROPERTY(EditAnywhere, Category = "Move Settings")
	float RestTime;

	// 是否正在移动
    bool bIsMoving;

	// 是否正在追击
	bool bIsChasing;

	// 是否正在休息
	bool bIsResting;

    // 是否待机
	bool bIsIdling;

    // 用于记录巡逻时间的计时器
    FTimerHandle PatrolTimerHandle;
    
    // 用于休息时间的计时器
    FTimerHandle RestTimerHandle;   

	// 移动组件
    TObjectPtr<UCharacterMovementComponent> EnemyMovement;
};


