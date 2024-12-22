#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/AttackInterface.h"
#include "GlobalTypes/GlobalTypes.h"
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
    virtual void NormalAttack(int AttackOpt) override;
    virtual void NormalRemoteAttack(int AttackOpt) override { return; };
    virtual void SkillAttack(int SkillOpt) override { return; };
    virtual bool CanAttack(int AttackOpt) const override;
    virtual bool CanRemoteAttack(int AttackOpt) const override { return false; }
    virtual bool CanSkillAttack(int SkillOpt) const override { return false; }
    virtual bool IsInRange(int AttackOpt) const override;
	virtual bool IsInRemoteRange(int AttackOpt) const override { return false; }
    virtual bool IsInSkillRange(int SkillOpt) const override { return false; }
    virtual bool GetIsAttacking(int AttackOpt) const override;
    virtual bool GetIsSkillAttacking(int SkillOpt) const override { return false; }

	UFUNCTION(BlueprintCallable)
    void AddAttack(FString Name, float CD, float Range, float Damage, float AnimDuration) { Attacks.Add(FAttack(Name, CD, Range, Damage, AnimDuration)); };

	UFUNCTION(BlueprintCallable)
    TArray<FAttack> GetAttacks() { return Attacks; };

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    //攻击数组
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	TArray<FAttack> Attacks;

    //攻击动画计时器句柄
	FTimerHandle AttackEndTimerHandle;

    // 攻击对象
    AActor* TargetActor;
};
