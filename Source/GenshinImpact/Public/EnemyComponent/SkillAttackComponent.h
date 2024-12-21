// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackInterface.h"
#include "SkillAttackComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API USkillAttackComponent : public UActorComponent, public IAttackInterface
{
    GENERATED_BODY()

public:
    USkillAttackComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void NormalAttack() override;
    virtual void NormalRemoteAttack() override { return; };
    virtual void SkillAttack(int SkillOpt) override;
    virtual bool CanAttack() const override;
	virtual bool CanRemoteAttack() const override { return false; };
    virtual bool CanSkillAttack() const override;
    virtual bool IsInRange() const override;
	virtual bool IsInRemoteRange() const override { return false; };
    virtual bool IsInSkillRange() const override;
    virtual bool GetIsAttacking() const override { return bIsAttacking; }
    virtual bool GetIsSkillAttacking() const override { return bIsSkillAttacking; }

protected:
    virtual void BeginPlay() override;

    // 攻击冷却时间
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackCooldown;

    // 技能冷却时间
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float SkillCooldown;

    // 攻击范围
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackRange;

    // 技能范围
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float SkillAttackRange;

    // 攻击伤害
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackDamage;

    // 技能伤害
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float SkillDamage;

    // 攻击动画时长
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float AttackAnimationDuration;

    // 技能动画时长
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float SkillAnimationDuration;

    // 攻击对象
    AActor* TargetActor;

    // 是否可以攻击
    bool bCanAttack;

    // 是否可以技能攻击
    bool bCanSkillAttack;

    // 重置攻击状态
    void ResetAttackCooldown() { bCanAttack = true; };

    // 重置技能攻击状态
    void ResetSkillCooldown() { bCanSkillAttack = true; };

    // 攻击冷却计时器句柄
    FTimerHandle AttackCooldownTimerHandle;

    // 技能冷却计时器句柄
    FTimerHandle SkillCooldownTimerHandle;

    // 攻击动画计时器句柄
    FTimerHandle AttackEndTimerHandle;

    // 是否正在攻击
    bool bIsAttacking;

    // 是否正在释放技能
    bool bIsSkillAttacking;
};
