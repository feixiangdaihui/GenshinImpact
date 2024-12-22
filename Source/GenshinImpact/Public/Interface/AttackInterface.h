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
	virtual void NormalAttack(int AttackOpt = 0) = 0;

	virtual void NormalRemoteAttack(int AttackOpt = 0) = 0;

	virtual void SkillAttack(int SkillOpt = 0) = 0;

	// 检查是否可以攻击目标
	virtual bool CanAttack(int AttackOpt = 0) const = 0;

	virtual bool CanRemoteAttack(int AttackOpt = 0) const = 0;

	virtual bool CanSkillAttack(int SkillOpt = 0) const = 0;

	// 是否在攻击范围
	virtual bool IsInRange(int AttackOpt = 0) const = 0;

	virtual bool IsInRemoteRange(int AttackOpt = 0) const = 0;

	virtual bool IsInSkillRange(int SkillOpt = 0) const = 0;

	virtual bool GetIsAttacking(int AttackOpt = 0) const = 0;

	virtual bool GetIsSkillAttacking(int SkillOpt = 0) const = 0;
};
