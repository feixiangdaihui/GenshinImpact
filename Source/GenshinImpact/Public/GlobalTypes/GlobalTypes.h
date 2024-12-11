// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalTypes.generated.h"
#define ELEMENTRESTRAINPOSITIVE 1.2
#define ELEMENTRESTRAINNEGATIVE 0.8
#define LEVELMODIFY 0.01

UENUM(BlueprintType)
enum class GElement : uint8
{
	Matel,
	Wood,
	Water,
	Fire,
	Earth,
};
UENUM(BlueprintType)
enum class GElementRestrain : uint8
{
	Negative ,
	Neutral,
	Positive ,
};


/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UGlobalTypes : public UObject
{
	GENERATED_BODY()
public:
	static GElementRestrain GetElementRestrain(GElement self, GElement other);
	static float CalculateDamage(float AttackPower, float ElementPower) { return AttackPower * ElementPower; };
	static float ModifyDamage(float Damage, int EnemyLevel, int CharacterLevel, GElement EnemyElement, GElement CharacterElement);
};
