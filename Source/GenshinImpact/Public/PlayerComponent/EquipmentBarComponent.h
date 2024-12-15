// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/Equipment/Equipment.h"
#include "EquipmentBarComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UEquipmentBarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentBarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void WearEquipment(AEquipment* Equipment);
	UFUNCTION(BlueprintCallable)
	void TakeOffEquipment(EEquipmentType& EquipmentType);
	int32 GetEquipmentNum() { return EquipmentBar.Num(); }
	TArray<TObjectPtr<AEquipment>> EquipmentBar;
	void UpdateAttribute();
		
};
