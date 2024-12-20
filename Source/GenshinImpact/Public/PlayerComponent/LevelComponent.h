// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Level",meta = (AllowPrivateAccess = "true"))
	int level;
	float Experience;
	const float ExperienceToLevelUp = 100.0f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Level")
	void AddExperience(float ExperienceToAdd);
	void LevelUp();
	void InitializeLevelComponent(int InitLevel, float InitExperience) { level = InitLevel; Experience = InitExperience; }
	float GetCurrentExperience() { return Experience; }
	int GetCurrentLevel() { return level; }
};
