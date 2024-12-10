#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class IEnemyHealthInterface;
class IAttackInterface;
class IMoveInterface;
class IDetectInterface;
class UAttackComponent;
class UMoveComponent;
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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAttackComponent> AttackComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMoveComponent> MoveComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDetectComponent> DetectComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEnemyHealthComponent> HealthComponent;

protected:
    virtual void BeginPlay() override;

public://外部接口
    AEnemyCharacter();

    virtual void Tick(float DeltaTime) override;

	void TakeDammageByValue(float DammageValue);

	void TakeDammageByPercent(float DammagePercent);

    GElement GetElement();
};
