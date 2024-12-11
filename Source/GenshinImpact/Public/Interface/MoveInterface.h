#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoveInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMoveInterface : public UInterface
{
    GENERATED_BODY()
};

class GENSHINIMPACT_API IMoveInterface
{
    GENERATED_BODY()

public:
    // 移动到指定位置
    virtual void MoveTo(const FVector& Location, float AcceptRadius) = 0;

    // 执行巡逻逻辑
    virtual void Patrol() = 0;

    // 追击玩家
    virtual void ChasePlayer() = 0;

    // 转向目标位置
    virtual void TurnTo(const FVector& TargetLocation, float DeltaTime) = 0;

    // 停止
	virtual void Stop() = 0;

	virtual bool GetIsMoving() const = 0;
	virtual bool GetIsChasing() const = 0;
	virtual bool GetIsResting() const = 0;
    virtual bool GetIsIdling() const = 0;
	virtual FVector GetSpawnLocation() const = 0;
};
