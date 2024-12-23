#include "GachaSystem/GachaSystem.h"
#include "Engine/Engine.h"

UGachaSystem::UGachaSystem()
{
    TotalWeight = 0;
}

void UGachaSystem::InitializeGacha()
{
    
    GachaItems.Empty();

    // 抽卡系统中卡片信息

    FGachaItem Item1;
    Item1.ItemName = "枪";
    Item1.Description = "";
    Item1.Rarity = 50; 
    GachaItems.Add(Item1);

    FGachaItem Item2;
    Item2.ItemName = "武器B";
    Item2.Description = "高攻击力的长剑";
    Item2.Rarity = 30;
    GachaItems.Add(Item2);

    FGachaItem Item3;
    Item3.ItemName = "角色C";
    Item3.Description = "辅助型角色";
    Item3.Rarity = 20;
    GachaItems.Add(Item3);

    // 计算总权重
    TotalWeight = 0;
    for (const FGachaItem& Item : GachaItems)
    {
        TotalWeight += Item.Rarity;
    }

    UE_LOG(LogTemp, Warning, TEXT("Gacha System Initialized with %d items. Total Weight: %d"), GachaItems.Num(), TotalWeight);
}

FGachaItem UGachaSystem::DrawGacha()
{
    if (GachaItems.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("GachaItems is empty! InitializeGacha first."));
        return FGachaItem();
    }

    int32 RandomValue = FMath::RandRange(1, TotalWeight);
    UE_LOG(LogTemp, Warning, TEXT("Random Value: %d"), RandomValue);

    int32 AccumulatedWeight = 0;
    for (const FGachaItem& Item : GachaItems)
    {
        AccumulatedWeight += Item.Rarity;
        if (RandomValue <= AccumulatedWeight)
        {
            UE_LOG(LogTemp, Warning, TEXT("Drawn Item: %s"), *Item.ItemName);
            return Item;
        }
    }

    return FGachaItem();
}


