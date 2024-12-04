// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalTypes.generated.h"

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

};
