#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/EnemyHealthInterface.h"
#include "GlobalTypes/GlobalTypes.h"
#include "EnemyComponent/EnemyHealthComponent.h"
#include "BossHealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API UBossHealthComponent : public UEnemyHealthComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBossHealthComponent();

protected:
	virtual void RestoreShield() override;

	// 最大护盾值
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float MaxShield;

	// 当前护盾值
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float CurrentShield;

	// 护盾回复量
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float ShieldHealAmount;

	// 技能数组
	UPROPERTY(EditAnywhere, Category = "Skill Settings")
	TArray<FSkill> Skills;

	// 技能动画计时器句柄
	FTimerHandle SkillEndTimerHandle;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TakeDamageByValue(float DamageAmount, float TimeToBeAttacked = 0.5f) override;
	virtual void TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked = 0.5f) override;
	virtual float GetCurrentShieldPercent() const override { return CurrentShield / MaxShield; }
	virtual bool GetIsUsingSkill(int SkillOpt) const;
	virtual void UseSkill(int SkillOpt) override;
};
