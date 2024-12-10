#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/EnemyHealthInterface.h"
#include "GlobalTypes/GlobalTypes.h"
#include "EnemyHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UEnemyHealthComponent : public UActorComponent, public IEnemyHealthInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Die() override;
	virtual void Heal() override;
	virtual void ResetBeAttacked() override { bIsBeingAttacked = false; }

	// 最大生命值
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float MaxHealth;

	// 当前生命值
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float CurrentHealth;

	// 回血量
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float HealAmount;

	// 等级
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float Level;

	// 是否死亡
	UPROPERTY(VisibleAnywhere, Category = "Health Settings")
	bool bIsDead;

	// 是否正在被攻击
	UPROPERTY(VisibleAnywhere, Category = "Health Settings")
	bool bIsBeingAttacked;

	// 元素类型
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	GElement ElementType;

	// 受击状态计时器
	FTimerHandle BeAttackedStateTimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TakeDamageByValue(float DamageAmount, float TimeToBeAttacked = 0.5f) override;
	virtual void TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked = 0.5f) override;
	virtual bool GetIsBeingAttacked() const override { return bIsBeingAttacked; }
	virtual bool GetIsDead() const override { return bIsDead; }
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const override { return MaxHealth; }
	virtual float GetCurrentHealth() const override { return CurrentHealth; }
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentHealthPercent() const override { return CurrentHealth / MaxHealth; }
	virtual GElement GetElementType() const override { return ElementType; }
	virtual float GetLevel() const override { return Level; }
};
