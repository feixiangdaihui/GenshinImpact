// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/Equipment/Equipment.h"
#include "EquipmentBarWidget.generated.h"
class UTexture2D;
class UImage;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UEquipmentBarWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> EquipmentBarDefault;
	//4个图片框
	UPROPERTY(meta = (BindWidget))
	TArray<UImage*> EquipmentImages;



public:
	UFUNCTION(BlueprintCallable)
	void UpdateEquipmentBar(int32 index,UTexture2D* Texture);
	UFUNCTION(BlueprintCallable)
	void TakeOffEquipment(int32 index);

	UFUNCTION(BlueprintCallable)
	void InitializeEquipmentImages(TArray<UImage*> Images) { EquipmentImages = Images; }
	
	void DefaultInitializeEquipmentBar();
};
