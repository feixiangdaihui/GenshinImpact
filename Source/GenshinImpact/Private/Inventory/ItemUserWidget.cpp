
#include "Inventory/ItemUserWidget.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

// ģ��ʵ�� ThrowItem ����
void UItemUserWidget::CPP_ThrowItem()
{
    // �����Ʒ�Ƿ�ɶ���
    if (CPP_SlotIndex >= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Simulating item thrown from slot: %d"), CPP_SlotIndex);

        // ģ���ȡ��ҵ�λ�úͷ���
        FVector PlayerLocation = FVector(0.f, 0.f, 100.f); // ��������λ��
        FVector ForwardVector = FVector(1.f, 0.f, 0.f); // �������������
        FVector SpawnLocation = PlayerLocation + ForwardVector * 200.f; // ��������λ��
        FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

        // ģ��������ƫ��
        FVector RandomOffset = FVector(FMath::RandRange(-50.f, 50.f), FMath::RandRange(-50.f, 50.f), 0.f);
        SpawnLocation += RandomOffset;

        // ģ������ Actor
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation);

        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Simulated item successfully thrown and spawned!"));
            // ģ���������Ч��
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

        // ģ�������Ʒ����
        UE_LOG(LogTemp, Warning, TEXT("Reducing item count for slot %d"), CPP_SlotIndex);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No items available to throw in slot: %d"), CPP_SlotIndex);
    }
}

// ģ��ʵ�� MouseLeave ����
void UItemUserWidget::CPP_MouseLeave()
{
    // ģ������뿪�߼�
    UE_LOG(LogTemp, Warning, TEXT("Simulating mouse leave from UI element."));

    // ��װִ��һЩ UI �������
    bool bMouseLeft = true; // ��������Ѿ��뿪
    if (bMouseLeft)
    {
        UE_LOG(LogTemp, Warning, TEXT("Mouse leave event successfully processed."));
    }
}

// ģ��ʵ�� UseItem ����
void UItemUserWidget::CPP_UseItem()
{
    // ����ʹ����Ʒ��ָ�����ֵ������ֵ
    if (CPP_SlotIndex >= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Simulating using item in slot: %d"), CPP_SlotIndex);

        // �������ֵ����ʹ��Ч��
        if (CPP_RandomInt % 3 == 0)
        {
            // ģ��ָ�����ֵ
            float HealthRestored = FMath::RandRange(10.f, 50.f); // �ָ� 10~50 ������ֵ
            UE_LOG(LogTemp, Warning, TEXT("Restoring health by %f"), HealthRestored);
        }
        else if (CPP_RandomInt % 3 == 1)
        {
            // ģ����������
            float ManaRestored = FMath::RandRange(5.f, 30.f); // ���� 5~30 ������
            UE_LOG(LogTemp, Warning, TEXT("Restoring mana by %f"), ManaRestored);
        }
        else
        {
            // ģ����������Ч��
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
