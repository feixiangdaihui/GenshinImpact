// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackInterface.h"
#include "GlobalTypes/GlobalTypes.h"
#include "SkillAttackComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API USkillAttackComponent : public UActorComponent, public IAttackInterface
{
    GENERATED_BODY()

public:
    USkillAttackComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void NormalAttack(int AttackOpt) override;
    virtual void NormalRemoteAttack(int AttackOpt) override { return; };
    virtual void SkillAttack(int SkillOpt) override;
    virtual bool CanAttack(int AttackOpt) const override;
	virtual bool CanRemoteAttack(int AttackOpt) const override { return false; };
    virtual bool CanSkillAttack(int SkillOpt) const override;
    virtual bool IsInRange(int AttackOpt) const override;
	virtual bool IsInRemoteRange(int AttackOpt) const override { return false; };
    virtual bool IsInSkillRange(int SkillOpt) const override;
    virtual bool GetIsAttacking(int AttackOpt) const override;
    virtual bool GetIsSkillAttacking(int SkillOpt) const override;

    UFUNCTION(BlueprintCallable)
    void AddAttack(FString Name, float CD, float Range, float Damage, float AnimDuration) { Attacks.Add(FAttack(Name, CD, Range, Damage, AnimDuration)); };

    UFUNCTION(BlueprintCallable)
    void AddSkill(FString Name, float CD, float Range, float Damage, float AnimDuration) { Skills.Add(FSkill(Name, CD, Range, Damage, AnimDuration)); };

    UFUNCTION(BlueprintCallable)
    TArray<FSkill> GetSkills() const { return Skills; }

    UFUNCTION(BlueprintCallable)
    TArray<FAttack> GetAttacks() const { return Attacks; }

protected:
    virtual void BeginPlay() override;

    // 攻击对象
    AActor* TargetActor;

    // 攻击动画计时器句柄
    FTimerHandle AttackEndTimerHandle;

    // 技能动画计时器句柄
	FTimerHandle SkillEndTimerHandle;

    // 攻击数组
	UPROPERTY(EditAnywhere, Category = "Attack Settings")
    TArray<FAttack> Attacks;

    // 技能数组
    UPROPERTY(EditAnywhere, Category = "Skill Settings")
    TArray<FSkill> Skills;
};
