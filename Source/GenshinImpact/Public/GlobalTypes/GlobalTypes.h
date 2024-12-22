// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalTypes.generated.h"
#define ELEMENTRESTRAINPOSITIVE 1.2
#define ELEMENTRESTRAINNEGATIVE 0.8
#define LEVELMODIFY 0.01
#define SKILL_HEAL 1
#define SKILL_RESTORE_SHIELD 2
#define SKILL_START 3
#define SKILL_END 6

UENUM(BlueprintType)
enum class GElement : uint8
{
	Matel,
	Wood,
	Water,
	Fire,
	Earth,
};
UENUM(BlueprintType)
enum class GElementRestrain : uint8
{
	Negative ,
	Neutral,
	Positive ,
};


/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UGlobalTypes : public UObject
{
	GENERATED_BODY()
public:
	static GElementRestrain GetElementRestrain(GElement self, GElement other);
	static float CalculateDamage(float AttackPower, float ElementPower) { return AttackPower * ElementPower; };
	static float ModifyDamage(float Damage, int EnemyLevel, int CharacterLevel, GElement EnemyElement, GElement CharacterElement);
};

USTRUCT(BlueprintType)
struct FSkill
{
    GENERATED_BODY()
public:
    // 技能名称
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FString SkillName;

    // 技能冷却时间（总时间）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float Cooldown;

    // 技能当前冷却剩余时间
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
    float CurrentCooldown;

    // 技能范围
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float Range;

    // 技能伤害
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float Damage;

    // 技能动画时长
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    float AnimationDuration;

    // 技能是否可以使用
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
    bool bCanUse;

    // 技能是否正在使用
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
    bool bIsUsing;

    // 构造函数
    FSkill() : SkillName("DefaultSkill"), Cooldown(0.f), CurrentCooldown(0.f), Range(0.f), Damage(0.f), AnimationDuration(0.f), bCanUse(true), bIsUsing(false) {}
    FSkill(FString Name, float CD, float Range, float Damage, float AnimDuration) : SkillName(Name), Cooldown(CD), CurrentCooldown(0.f), Range(Range), Damage(Damage), AnimationDuration(AnimDuration), bCanUse(true), bIsUsing(false) {}
};

USTRUCT(BlueprintType)
struct FAttack
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FString AttackName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Cooldown;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
    float CurrentCooldown;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Range;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float Damage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    float AnimationDuration;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
    bool bCanUse;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
    bool bIsUsing;
    FAttack() : AttackName("DefaultAttack"), Cooldown(0.f), CurrentCooldown(0.f), Range(0.f), Damage(0.f), AnimationDuration(0.f), bCanUse(true), bIsUsing(false) {}
    FAttack(FString Name, float CD, float Range, float Damage, float AnimDuration) : AttackName(Name), Cooldown(CD), CurrentCooldown(0.f), Range(Range), Damage(Damage), AnimationDuration(AnimDuration), bCanUse(true), bIsUsing(false) {};
};
