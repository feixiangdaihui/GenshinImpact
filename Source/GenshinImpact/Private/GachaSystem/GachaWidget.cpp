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

    // �󶨰�ť����¼�
    if (GachaButton)
    {
        GachaButton->OnClicked.AddDynamic(this, &UGachaWidget::OnGachaButtonClicked);
    }

    // ��ʼ������ı�
    if (ResultText)
    {
        ResultText->SetText(FText::FromString(TEXT("�ȴ��鿨���...")));
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

            UpdateResultText(FString::Printf(TEXT("�鿨���: %s"), *DrawnItem.ItemName));

            GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
                {
                    FTimerHandle TimerHandle;
                    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGachaWidget::DisplaySuccessMessage, 2.0f, false);
                });
        }
    }
    else
    {
        UpdateResultText(TEXT("δ�ҵ��鿨��������"));
    }
}

void UGachaWidget::DisplaySuccessMessage()
{
    UpdateResultText(TEXT("�鿨�ɹ���"));
}

void UGachaWidget::UpdateResultText(const FString& NewResult)
{
    if (ResultText)
    {
        ResultText->SetText(FText::FromString(NewResult));
    }
}
