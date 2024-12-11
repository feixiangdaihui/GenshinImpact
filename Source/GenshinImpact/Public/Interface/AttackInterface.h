#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAttackInterface : public UInterface
{
    GENERATED_BODY()
};

class GENSHINIMPACT_API IAttackInterface
{
    GENERATED_BODY()

public:
    // 普通攻击方法
    virtual void NormalAttack() = 0;

    // 检查是否可以攻击目标
    virtual bool CanAttack() const = 0;

    // 是否在攻击范围
	virtual bool IsInRange() const = 0;

	virtual bool GetIsAttacking() const = 0;
};
