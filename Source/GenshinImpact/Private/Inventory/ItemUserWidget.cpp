
#include "Inventory/ItemUserWidget.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// 模拟实现 ThrowItem 函数
void UItemUserWidget::CPP_ThrowItem()
{
    // 检查物品是否可丢弃
    if (CPP_SlotIndex >= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Simulating item thrown from slot: %d"), CPP_SlotIndex);

        // 模拟获取玩家的位置和方向
        FVector PlayerLocation = FVector(0.f, 0.f, 100.f); // 假设的玩家位置
        FVector ForwardVector = FVector(1.f, 0.f, 0.f); // 假设的抛掷方向
        FVector SpawnLocation = PlayerLocation + ForwardVector * 200.f; // 计算生成位置
        FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

        // 模拟添加随机偏移
        FVector RandomOffset = FVector(FMath::RandRange(-50.f, 50.f), FMath::RandRange(-50.f, 50.f), 0.f);
        SpawnLocation += RandomOffset;

        // 模拟生成 Actor
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation);

        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Simulated item successfully thrown and spawned!"));
            // 模拟添加物理效果
            UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
            if (PrimitiveComp)
            {
                FVector Impulse = ForwardVector * 500.f + RandomOffset;
                PrimitiveComp->AddImpulse(Impulse, NAME_None, true);
                UE_LOG(LogTemp, Warning, TEXT("Applied impulse to spawned item!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Simulated item spawn failed."));
        }

        // 模拟减少物品数量
        UE_LOG(LogTemp, Warning, TEXT("Reducing item count for slot %d"), CPP_SlotIndex);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No items available to throw in slot: %d"), CPP_SlotIndex);
    }
}

// 模拟实现 MouseLeave 函数
void UItemUserWidget::CPP_MouseLeave()
{
    // 模拟鼠标离开逻辑
    UE_LOG(LogTemp, Warning, TEXT("Simulating mouse leave from UI element."));

    // 假装执行一些 UI 清理操作
    bool bMouseLeft = true; // 假设鼠标已经离开
    if (bMouseLeft)
    {
        UE_LOG(LogTemp, Warning, TEXT("Mouse leave event successfully processed."));
    }
}

// 模拟实现 UseItem 函数
void UItemUserWidget::CPP_UseItem()
{
    // 假设使用物品会恢复生命值或能量值
    if (CPP_SlotIndex >= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Simulating using item in slot: %d"), CPP_SlotIndex);

        // 根据随机值决定使用效果
        if (CPP_RandomInt % 3 == 0)
        {
            // 模拟恢复生命值
            float HealthRestored = FMath::RandRange(10.f, 50.f); // 恢复 10~50 点生命值
            UE_LOG(LogTemp, Warning, TEXT("Restoring health by %f"), HealthRestored);
        }
        else if (CPP_RandomInt % 3 == 1)
        {
            // 模拟增加蓝量
            float ManaRestored = FMath::RandRange(5.f, 30.f); // 增加 5~30 点蓝量
            UE_LOG(LogTemp, Warning, TEXT("Restoring mana by %f"), ManaRestored);
        }
        else
        {
            // 模拟其他增益效果
            float DamageBoost = FMath::RandRange(5.f, 20.f); 
            float SpeedBoost = FMath::RandRange(1.f, 10.f); 
            UE_LOG(LogTemp, Warning, TEXT("Boosting damage by %f and speed by %f"), DamageBoost, SpeedBoost);
        }

        if (CPP_SlotIndex % 2 == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("Simulated item consumed successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Simulated item partially consumed."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No items available to use in slot: %d"), CPP_SlotIndex);
    }
}
