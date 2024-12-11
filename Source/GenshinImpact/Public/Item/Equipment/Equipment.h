// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"
#define EEquipmentType_MAX 4
UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	FirstPosition,
	SecondPosition,
	ThirdPosition,
	FourthPosition,
};
UCLASS()
class GENSHINIMPACT_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment();




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetEquipmentType(EEquipmentType WantType);
	EEquipmentType GetEquipmentType() const { return EquipmentType; }
	EEquipmentType EquipmentType;
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float AttackPower;
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float ElementPower;
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float HealthPower;
};
