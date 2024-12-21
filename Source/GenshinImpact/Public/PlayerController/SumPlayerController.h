// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "InputActionValue.h"
#include "Inventory/CPP_InventoryComponent.h"
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
public:
	TObjectPtr<ABaseHud> Hud;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void InitializeCharacterMessageAtBeginPlay();
	void ChangeCharacter(int CharacterIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<APlayCharacter>> CharacterClasses;


	TArray<TObjectPtr<APlayCharacter>> Characters;
	int CurrentCharacterIndex;

	void SetCharacterVisibility(int32 CharacterIndex, bool bVisible);

	void SeqChangeCharacter();

	void SaveCharacterData();
	void LoadCharacterData();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupInputComponent() override;

	// Toggle Inventory Widget
	void ToggleInventory();

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InventoryMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleInventoryAction;  

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCPP_InventoryComponent* InventoryComponent;
};
