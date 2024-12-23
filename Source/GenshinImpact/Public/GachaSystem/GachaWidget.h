#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GachaWidget.generated.h"

UCLASS()
class GENSHINIMPACT_API UGachaWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Called when the widget is constructed
    virtual void NativeConstruct() override;

protected:
    // Button for triggering Gacha
    UPROPERTY(meta = (BindWidget))
    class UButton* GachaButton;

    // Text block for displaying Gacha results
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ResultText;

    // Function to handle Gacha button click
    UFUNCTION()
    void OnGachaButtonClicked();

    // Function to display success message after delay
    void DisplaySuccessMessage();

public:
    // Function to update the result text
    UFUNCTION(BlueprintCallable, Category = "Gacha")
    void UpdateResultText(const FString& NewResult);
};
