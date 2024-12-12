// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UBlueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float MaxBlue ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float CurrentBlue ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float BlueRecoverTick;
	UFUNCTION(BlueprintCallable, Category = "Blue")
	void RecoverBlueByTick();
	UFUNCTION(BlueprintCallable, Category = "Blue")
	void AddBlue(float BlueValue);
	UFUNCTION(BlueprintCallable, Category = "Blue")
	bool ReduceBlue(float BlueValue);
		
};
