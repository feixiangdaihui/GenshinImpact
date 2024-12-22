// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "EquipmentWidget.generated.h"
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	//提示文本
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlockTips;
public:
	void SetTipsText(FText TipsText) { TextBlockTips->SetText(TipsText); }
	void SetTextRotation(FVector Rotation);
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
};
