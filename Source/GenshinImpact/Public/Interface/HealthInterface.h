// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GENSHINIMPACT_API IHealthInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void TakeDamageByValue(float DamageAmount);
	virtual void TakeDamageByValue_Implementation(float DamageAmount) = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void Die();
	virtual void Die_Implementation() = 0;
};
