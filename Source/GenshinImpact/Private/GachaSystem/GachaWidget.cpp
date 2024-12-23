#include "GachaSystem/GachaWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GachaSystem/GachaManagerActor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "PlayerController/SumPlayerController.h" 

void UGachaWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 绑定按钮点击事件
    if (GachaButton)
    {
        GachaButton->OnClicked.AddDynamic(this, &UGachaWidget::OnGachaButtonClicked);
    }

    // 初始化结果文本
    if (ResultText)
    {
        ResultText->SetText(FText::FromString(TEXT("等待抽卡结果...")));
    }
}

void UGachaWidget::OnGachaButtonClicked()
{
    TArray<AActor*> GachaManagers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGachaManagerActor::StaticClass(), GachaManagers);

    if (GachaManagers.Num() > 0)
    {
        AGachaManagerActor* GachaManager = Cast<AGachaManagerActor>(GachaManagers[0]);
        if (GachaManager)
        {
            FGachaItem DrawnItem = GachaManager->PerformGacha();

            UpdateResultText(FString::Printf(TEXT("抽卡结果: %s"), *DrawnItem.ItemName));

            GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
                {
                    FTimerHandle TimerHandle;
                    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGachaWidget::DisplaySuccessMessage, 2.0f, false);
                });
        }
    }
    else
    {
        UpdateResultText(TEXT("未找到抽卡管理器！"));
    }
}

void UGachaWidget::DisplaySuccessMessage()
{
    UpdateResultText(TEXT("抽卡成功！"));
}

void UGachaWidget::UpdateResultText(const FString& NewResult)
{
    if (ResultText)
    {
        ResultText->SetText(FText::FromString(NewResult));
    }
}
