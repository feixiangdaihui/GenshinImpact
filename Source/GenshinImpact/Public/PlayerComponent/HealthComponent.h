// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UFUNCTION(BlueprintCallable, Category = "Health")
	void DamageHealthByValue(float DamageValue);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void DamageHealthByRate(float DamageRate);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void RecoverHealthByValue(float RecoverValue);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void RecoverHealthByRate(float DamageRate);

private:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float BaseHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float RemainHealthRate = 1.0f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMaxHealth(float NewMaxHealth);
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() { return MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() { return CurrentHealth; }
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddMaxHealth(float HealthToAdd);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void MinusMaxHealth(float HealthToMinus);

	void InitializeHealthComponent(float InitHealth);



		
};
