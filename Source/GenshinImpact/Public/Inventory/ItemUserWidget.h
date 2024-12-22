#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "ItemUserWidget.generated.h"


UCLASS()
class GENSHINIMPACT_API UItemUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // ģ�ⰴť���
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UButton* CPP_Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UButton* CPP_Button_0;

    // ģ�����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 CPP_SlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 CPP_RandomInt;

    // ��������
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_ThrowItem();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void CPP_MouseLeave();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_UseItem();
};

