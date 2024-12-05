#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DetectInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDetectInterface : public UInterface
{
    GENERATED_BODY()
};

class GENSHINIMPACT_API IDetectInterface
{
    GENERATED_BODY()

public:
    // 检测玩家是否在视野范围内
    virtual bool DetectPlayer(const FVector& OwnerLocation, const FVector& OwnerForwardVector, float SightRadius, float SightAngle) = 0;

    // 检测是否在听力范围内
    virtual bool DetectSound(const FVector& OwnerLocation, float HearingRadius) = 0;
};
