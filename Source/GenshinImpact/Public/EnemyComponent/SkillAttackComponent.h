// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalTypes/GlobalTypes.h"
#include "EnemyComponent/AttackComponent.h"
#include "SkillAttackComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API USkillAttackComponent : public UAttackComponent
{
    GENERATED_BODY()

public:
    USkillAttackComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void SkillAttack(int SkillOpt) override;
    virtual bool CanSkillAttack(int SkillOpt) const override;
    virtual bool IsInSkillRange(int SkillOpt) const override;
    virtual bool GetIsSkillAttacking(int SkillOpt) const override;

    UFUNCTION(BlueprintCallable)
    void AddSkill(FString Name, float CD, float Range, float Damage, float AnimDuration) { Skills.Add(FSkill(Name, CD, Range, Damage, AnimDuration)); };

    UFUNCTION(BlueprintCallable)
    TArray<FSkill> GetSkills() const { return Skills; }

protected:
    virtual void BeginPlay() override;

    // 技能动画计时器句柄
	FTimerHandle SkillEndTimerHandle;

    // 技能数组
    UPROPERTY(EditAnywhere, Category = "Skill Settings")
    TArray<FSkill> Skills;
};
