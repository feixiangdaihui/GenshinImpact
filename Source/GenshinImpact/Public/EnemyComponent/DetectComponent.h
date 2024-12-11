#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/DetectInterface.h"
#include "DetectComponent.generated.h"

class ACharacter;

/**
 * 负责实现 IDetectInterface 的检测组件
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API UDetectComponent : public UActorComponent, public IDetectInterface
{
    GENERATED_BODY()

public:
    UDetectComponent();

    // IDetectInterface 实现
    virtual bool DetectPlayer() override;
    virtual bool DetectSound() override;
	virtual bool GetCanDetectPlayer() const override { return bCanDetectPlayer; }
	virtual FVector GetLastPerceptionLocation() const { return LastPerceptionLocation; }

protected:
    virtual void BeginPlay() override;

private:
    // 缓存玩家引用
    ACharacter* PlayerCharacter;

    // 缓存最后感知位置
    FVector LastPerceptionLocation;

    // 是否能感知玩家
    bool bCanDetectPlayer;

    // 视觉半径
	UPROPERTY(EditAnywhere, Category = "Detection Settings")
	float SightRadius;

	// 视觉角度
	UPROPERTY(EditAnywhere, Category = "Detection Settings")
	float SightAngle;
};
