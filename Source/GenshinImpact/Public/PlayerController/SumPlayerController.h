// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SumPlayerController.generated.h"
#define CHARACTERNUM 3
class ABaseHud;
class APlayCharacter;
/**
 * 
 */
class ABaseHud;
UCLASS()
class GENSHINIMPACT_API ASumPlayerController : public APlayerController
{
	GENERATED_BODY()
	int CurrentCharacterIndex=0;
public:
	virtual void BeginPlay() override;
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

};
