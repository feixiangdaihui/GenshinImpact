// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SumPlayerController.generated.h"
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
public:
	TObjectPtr<ABaseHud> Hud;
	virtual void BeginPlay() override;
	void InitializeCharacterMessageAtBeginPlay();
	void ChangeCharacter(int CharacterIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<APlayCharacter>> CharacterClasses;


	TArray<TObjectPtr<APlayCharacter>> Characters;
	int CurrentCharacterIndex;

	void SetCharacterVisibility(int32 CharacterIndex, bool bVisible);

	void SeqChangeCharacter();


};
