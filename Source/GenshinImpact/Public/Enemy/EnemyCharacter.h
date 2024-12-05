#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;
class UAttackComponent;
class UMoveComponent;
class UDetectComponent;

UCLASS()
class GENSHINIMPACT_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()
	friend class AEnemyAIController;
    friend class UEnemyAnim;

protected://内部变量
    // 血量组件
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    TObjectPtr<UHealthComponent> HealthComponent;

    // 移动组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<class UMoveComponent> MoveComponent;

    // 攻击组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	TObjectPtr<class UAttackComponent> AttackComponent;
	
    // 感知组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detection")
    TObjectPtr<class UDetectComponent> DetectComponent;

public://外部接口
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

	void UpdateMovementSpeed();
};
