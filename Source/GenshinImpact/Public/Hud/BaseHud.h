// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHud.generated.h"
class URealTimeWidget;
class ASumPlayerController;
class APlayCharacter;
class UEquipmentBarWidget;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API ABaseHud : public AHUD
{
	GENERATED_BODY()
protected:
	int CurrentCharacterIndex;
	
	//RealTimeWidget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TArray<TSubclassOf<URealTimeWidget>> RealTimeWidgetClasses;



	UPROPERTY()
	TObjectPtr<ASumPlayerController> PlayerController;
	TArray<TObjectPtr<APlayCharacter>> Characters;

	TArray<TObjectPtr<URealTimeWidget>> RealTimeWidgets;

	//EquipmentBarWidget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UEquipmentBarWidget> EquipmentBarWidgetClass;

	TArray<TObjectPtr<UEquipmentBarWidget>> EquipmentBarWidget;
public:
	ABaseHud();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void UpdateRealTimeWidget();
	void AddEquipmentBarWidget(int32 CharacterIndex, int32 index, UTexture2D* Texture);
	void RemoveEquipmentBarWidget(int32 CharacterIndex, int32 index);
	void ChangeCharacterUI();
	void LoadEquipmentBarWidget();
};
