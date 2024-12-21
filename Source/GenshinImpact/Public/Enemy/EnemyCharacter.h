#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class IEnemyHealthInterface;
class IAttackInterface;
class IMoveInterface;
class IDetectInterface;
class UAttackComponent;
class URemoteAttackComponent;
class UMoveComponent;
class UImmobileomponent;
class UDetectComponent;
class UEnemyHealthComponent;
enum class GElement : uint8;

UCLASS()
class GENSHINIMPACT_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()
    friend class AEnemyAIController;
    friend class UEnemyAnim;

protected://内部变量
    IAttackInterface* AttackInterface;
    IMoveInterface* MoveInterface;
    IDetectInterface* DetectInterface;
    IEnemyHealthInterface* HealthInterface;

    /*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAttackComponent> AttackComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMoveComponent> MoveComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDetectComponent> DetectComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEnemyHealthComponent> HealthComponent;*/

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<UActorComponent> AttackComponentClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<UActorComponent> MoveComponentClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<UActorComponent> DetectComponentClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<UActorComponent> HealthComponentClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UActorComponent> AttackComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UActorComponent> MoveComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UActorComponent> DetectComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UActorComponent> HealthComponent;

protected:
    virtual void BeginPlay() override;

    //角色销毁定时器句柄
    FTimerHandle DestroyTimerHandle;

    //敌人死亡销毁时间
	UPROPERTY(EditAnywhere, Category = "Enemy Settings")
	float DestroyTime;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
    bool bIsDead;

public://外部接口
    AEnemyCharacter();

    virtual void Tick(float DeltaTime) override;

    void TakeDamageByValue(float DammageValue);

    void TakeDamageByPercent(float DammagePercent);

    GElement GetElementType() const;

    float GetLevel() const;

    UFUNCTION(BlueprintCallable)
    float GetCurrentHealthPercent() const;
};
