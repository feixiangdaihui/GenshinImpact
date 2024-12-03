#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;

UCLASS()
class GENSHINIMPACT_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()
	friend class AEnemyAIController;
    friend class UEnemyAnim;

protected://内部变量
    // 出生点位置
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    FVector SpawnLocation;

    // 血量属性
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentHealth;

    // 最大血量
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float MaxHealth;

    // 回血量
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float HealHealth;

    // 攻击力
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float AttackPower;

    // 攻击范围
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float AttackRange;

    // 攻击间隔
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackInterval;

    // 走路速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float WalkSpeed;

    // 跑步速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float RunSpeed;

    // 转身速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float RotationRate;

    // 当前速度
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    float CurrentSpeed;

    // 是否正在攻击
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    bool IsAttacking;

    // 是否正在被攻击
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    bool IsBeingAttacked;

    // 是否死亡
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    bool IsDead;

    // 是否坐下
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool IsSitting;

    // 是否巡逻
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
	bool IsPatrol;

    // 巡逻范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatrolRange;

    // 感知范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRange;

    // 感知角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionAngle;

	// 是否能看到玩家
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	bool PlayerInSight;

    // 定时器句柄
    FTimerHandle HealTimerHandle;                // 用于回血的定时器
    FTimerHandle ResetBeingAttackedTimerHandle;  // 重置被攻击状态的定时器
    FTimerHandle ResetAttackingTimerHandle;      // 重置攻击状态的定时器
	float SittingTimer;						  // 坐下时间
	float PatrolTimer;                            // 巡逻时间

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    TObjectPtr<UHealthComponent> HealthComponent;

public://外部接口
    // 构造函数
    AEnemyCharacter();

    // 受伤函数
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void TakeDamage(float DamageAmount);

    // 攻击函数
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Attack();

    // 死亡处理
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Die();

    // 回血函数
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void HealOverTime();

    // 获取出生点位置
    UFUNCTION(BlueprintCallable, Category = "Stats")
    FVector GetSpawnLocation() const;

    // 获取攻击范围
    UFUNCTION(BlueprintCallable, Category = "Stats")
    float GetAttackRange() const;

	// 获取感知范围
	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetDetectionRange() const;

	// 获取上一次伤害方向
	FVector GetLastDamageDirection() const;

    //// 判断状态（静止，行走，跑步）
    //UFUNCTION(BlueprintCallable, Category = "Actions")
    //CharacterState GetCharacterState();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

	void UpdateMovementSpeed();
};
