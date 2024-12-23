// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "InputActionValue.h"
#include "GachaSystem/GachaWidget.h"
#include "SumPlayerController.generated.h"
#define CHARACTERNUM 3

class APlayCharacter;
/**
 * 
 */
class ABaseHud;

UCLASS()
class GENSHINIMPACT_API ASumPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	int CurrentCharacterIndex = 0;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void InitializeCharacterMessageAtBeginPlay();

	void ChangeCharacter(int CharacterIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<APlayCharacter>> CharacterClasses;

	TArray<TObjectPtr<APlayCharacter>> Characters;

	void SetCharacterVisibility(int32 CharacterIndex, bool bVisible);

	void SeqChangeCharacter();

	void SaveCharacterData();

	void LoadCharacterData();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	int GetCurrentCharacterIndex() { return CurrentCharacterIndex; }

private:
 
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UGachaWidget> GachaWidgetClass;

	UGachaWidget* GachaWidgetInstance;

	bool bIsGachaUIVisible;

	void ToggleGachaUI();


	UFUNCTION()
	bool CheckIsAllCharacterDead();

	UFUNCTION()
	void GameOver();
};
