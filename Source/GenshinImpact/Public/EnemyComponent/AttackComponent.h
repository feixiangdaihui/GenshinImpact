#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackInterface.h"
#include "AttackComponent.generated.h"

/**
 * 攻击组件，用于实现普通攻击逻辑
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API UAttackComponent : public UActorComponent, public IAttackInterface
{
    GENERATED_BODY()

public:
    UAttackComponent();

    // IAttackInterface 实现
    virtual void NormalAttack() override;
    virtual bool CanAttack() const override;
	virtual bool IsInRange() const override;
	virtual bool GetIsAttacking() const override { return bIsAttacking; }

protected:
    virtual void BeginPlay() override;

private:
    // 攻击冷却时间
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackCooldown;

    // 攻击范围
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackRange;

    // 攻击伤害
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackDamage;

    // 攻击动画时长
	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float AttackAnimationDuration;

    // 攻击对象
    AActor* TargetActor;

    // 是否可以攻击
    bool bCanAttack;

    // 重置攻击状态
    void ResetAttackCooldown();

    // 攻击冷却计时器句柄
    FTimerHandle AttackCooldownTimerHandle;

	// 攻击动画计时器句柄
    FTimerHandle AttackEndTimerHandle;

    // 是否正在攻击
    bool bIsAttacking;
};
