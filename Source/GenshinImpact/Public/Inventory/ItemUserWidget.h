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
    // 模拟按钮组件
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UButton* CPP_Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UButton* CPP_Button_0;

    // 模拟变量
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 CPP_SlotIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logic")
    int32 CPP_RandomInt;

    // 函数声明
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_ThrowItem();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void CPP_MouseLeave();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_UseItem();
};

