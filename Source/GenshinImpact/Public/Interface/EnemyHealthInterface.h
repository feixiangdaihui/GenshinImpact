// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GlobalTypes/GlobalTypes.h"
#include "EnemyHealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyHealthInterface : public UInterface
{
	GENERATED_BODY()
};

class GENSHINIMPACT_API IEnemyHealthInterface
{
	GENERATED_BODY()

public:
	virtual void TakeDamageByValue(float DamageAmount, float TimeToBeAttacked = 0.5f) = 0;
	virtual void TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked = 0.5f) = 0;
	virtual bool GetIsBeingAttacked() const = 0;
	virtual bool GetIsDead() const = 0;
	virtual bool GetIsUsingSkill(int SkillOpt = 0) const = 0;
	virtual float GetMaxHealth() const = 0;
	virtual float GetCurrentHealth() const = 0;
	virtual float GetCurrentHealthPercent() const = 0;
	virtual float GetCurrentShieldPercent() const = 0;
	virtual GElement GetElementType() const = 0;
	virtual float GetLevel() const = 0;
	virtual void ConveyExperience() const = 0;
	virtual void UseSkill(int SkillOpt = 0) = 0;

protected:
	virtual void Heal() = 0;
	virtual void RestoreShield() = 0;
	virtual void Die() = 0;
	virtual void ResetBeAttacked() = 0;
};
