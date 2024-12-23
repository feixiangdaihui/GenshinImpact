#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GachaSystem.h"
#include "GachaManagerActor.generated.h"

UCLASS()
class GENSHINIMPACT_API AGachaManagerActor : public AActor
{
    GENERATED_BODY()

public:
    AGachaManagerActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    UGachaSystem* GachaSystemInstance;

    UFUNCTION(BlueprintCallable, Category = "Gacha")
    FGachaItem PerformGacha();
};
