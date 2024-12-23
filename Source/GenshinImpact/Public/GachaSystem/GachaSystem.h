#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GachaSystem.generated.h"

// 定义一个结构体来表示可以抽取的物品
USTRUCT(BlueprintType)
struct FGachaItem
{
    GENERATED_BODY()

public:
    // 物品的名称
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
    FString ItemName;

    // 物品的描述
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
    FString Description;

    // 物品的稀有度（用于概率计算）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
    int32 Rarity;
};

// 定义Gacha系统的主类
UCLASS(Blueprintable)
class GENSHINIMPACT_API UGachaSystem : public UObject
{
    GENERATED_BODY()

public:
    UGachaSystem();

    // 初始化抽卡系统，加载可抽取的物品
    UFUNCTION(BlueprintCallable, Category = "Gacha")
    void InitializeGacha();

    // 执行一次抽卡
    UFUNCTION(BlueprintCallable, Category = "Gacha")
    FGachaItem DrawGacha();

private:
    // 可抽取的物品列表
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha", meta = (AllowPrivateAccess = "true"))
    TArray<FGachaItem> GachaItems;

    int32 TotalWeight;
};
