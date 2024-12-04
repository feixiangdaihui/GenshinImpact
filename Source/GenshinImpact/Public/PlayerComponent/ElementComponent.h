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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//元素类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	GElement ElementType;
	//元素精通
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	float BaseElementPower;
	void UpdateElementPower();
	//总元素精通
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Element")
	float SumElementPower;
		
};
