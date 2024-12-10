// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"GlobalTypes/GlobalTypes.h"
#include "ElementComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UElementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Called every frame

	//元素类型
	UPROPERTY(EditAnywhere, Category = "Element")
	GElement ElementType;
	//元素精通
	UPROPERTY(EditAnywhere, Category = "Element")
	float BaseElementPower;

	//总元素精通
	UPROPERTY(EditAnywhere, Category = "Element")
	float SumElementPower;
public:
	void UpdateElementPower();
	float GetElementPower() { return SumElementPower; }
	GElement GetElementType() { return ElementType; }
};
