// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnim.generated.h"

class AEnemyCharacter;

UCLASS()
class GENSHINIMPACT_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    // 更新动画属性的函数
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    // 初始化和绑定到拥有者
    virtual void NativeInitializeAnimation() override;

protected:
    // 动画相关的属性
    // 当前速度
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    float CurrentSpeed;

    // 是否正在攻击
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool IsAttacking;

    // 是否正在被攻击
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool IsBeingAttacked;

    // 是否死亡
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool IsDead;

    // 是否坐下
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool IsSitting;

    // 是否巡逻
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool IsPatrol;

    // 是否能看到玩家
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool PlayerInSight;

    // 行走速度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float WalkSpeed;
	
    // 跑步速度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float RunSpeed;

	// 引用到动画拥有者（敌人角色）
	TObjectPtr<AEnemyCharacter> EnemyCharacter;
};
