// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackPowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UAttackPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackPowerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//基础攻击力
	UPROPERTY(EditAnywhere, Category = "Attack")
	float BaseAttackPower;
	//总攻击力
	UPROPERTY(EditAnywhere, Category = "Attack")
	float SumAttackPower;
public:
	//更新攻击力
	UFUNCTION(BlueprintCallable)
	
	float GetAttackPower() { return SumAttackPower; }
	float GetBaseAttackPower() { return BaseAttackPower; }
	void AddAttackPower(float AttackPower) { SumAttackPower += AttackPower; }
	void MinusAttackPower(float AttackPower) { SumAttackPower -= AttackPower; }
};

