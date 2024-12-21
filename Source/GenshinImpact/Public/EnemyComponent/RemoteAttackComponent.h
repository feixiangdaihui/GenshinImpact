// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackInterface.h"
#include "RemoteAttackComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API URemoteAttackComponent : public UActorComponent, public IAttackInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    URemoteAttackComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void NormalAttack() override { return; };
    virtual void NormalRemoteAttack() override;
    virtual void SkillAttack(int SkillOpt) override { return; };
    virtual bool CanAttack() const override { return false; }
	virtual bool CanRemoteAttack() const override;
    virtual bool CanSkillAttack() const override { return false; }
    virtual bool IsInRange() const override { return false; };
	virtual bool IsInRemoteRange() const override;
    virtual bool IsInSkillRange() const override { return false; }
    virtual bool GetIsAttacking() const override { return bIsRemoteAttacking; }
    virtual bool GetIsSkillAttacking() const override { return false; }

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // 攻击冷却时间
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float RemoteAttackCooldown;

    // 攻击范围
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float RemoteAttackRange;

    // 攻击伤害
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float RemoteAttackDamage;

    // 攻击动画时长
    UPROPERTY(EditAnywhere, Category = "Attack Settings")
    float RemoteAttackAnimationDuration;

    // 攻击对象
    AActor* TargetActor;

    // 是否可以攻击
    bool bCanRemoteAttack;

    // 重置攻击状态
    void ResetRemoteAttackCooldown();

    // 攻击冷却计时器句柄
    FTimerHandle RemoteAttackCooldownTimerHandle;

    // 攻击动画计时器句柄
    FTimerHandle RemoteAttackEndTimerHandle;

    // 是否正在攻击
    bool bIsRemoteAttacking;
};
