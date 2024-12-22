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
    // 是否正在攻击
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsAttacking;

    //是否正在使用攻击技能
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsSkillAttacking;

    //是否正在使用恢复技能
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsUsingHealthSkill;

    // 是否正在被攻击
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsBeingAttacked;

    // 是否死亡
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsDead;

    // 是否休息
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    bool bIsResting;

    // 是否追击
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsChasing;

    // 是否巡逻
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsMoving;

    // 是否待机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsIdling;

    // 是否能看到玩家
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bCanDetectPlayer;

    // 玩家是否在攻击范围
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsInRange;

	// 引用到动画拥有者（敌人角色）
	TObjectPtr<AEnemyCharacter> EnemyCharacter;
};
