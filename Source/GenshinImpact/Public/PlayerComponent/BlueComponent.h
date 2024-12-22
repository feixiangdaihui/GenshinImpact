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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue", meta = (AllowPrivateAccess = "true"))
	float MaxBlue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue", meta = (AllowPrivateAccess = "true"))
	float CurrentBlue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue", meta = (AllowPrivateAccess = "true"))
	float BlueRecoverTick;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Blue")
	void RecoverBlueByTick();
	UFUNCTION(BlueprintCallable, Category = "Blue")
	void AddBlue(float BlueValue);
	UFUNCTION(BlueprintCallable, Category = "Blue")
	void AddBlueByRate(float Rate);
	UFUNCTION(BlueprintCallable, Category = "Blue")
	bool ReduceBlue(float BlueValue);
	UFUNCTION(BlueprintCallable, Category = "Blue")
	float GetCurrentBlue() { return CurrentBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	float GetMaxBlue() { return MaxBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	void SetMaxBlue(float NewMaxBlue) { MaxBlue = NewMaxBlue; }
	UFUNCTION(BlueprintCallable, Category = "Blue")
	void RecoverBlueByValue(float BlueValue);
	void InitializeBlueComponent(float InitBlue) { CurrentBlue = InitBlue; }
		
};
