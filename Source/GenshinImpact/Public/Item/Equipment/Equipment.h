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
class UEquipmentWidget;
class UTexture2D;
class USphereComponent;
class UWidgetComponent;
UCLASS()
class GENSHINIMPACT_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment();
	virtual void BeginPlay() override;



protected:
	// Called when the game starts or when spawned

	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	EEquipmentType EquipmentType;
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float AttackPower;
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float ElementPower;
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float HealthPower;
	//网格体
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	//纹理
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Texture;

	//按键拾取文本
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	FString PickupText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UWidgetComponent> EquipmentWidgetComponent;
	TObjectPtr<UEquipmentWidget> EquipmentWidget;

	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	float NeedToShowDistance=500;

	//碰撞体
	UPROPERTY(EditAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetEquipmentType(EEquipmentType WantType);
	EEquipmentType GetEquipmentType() const { return EquipmentType; }
	float GetAttackPower() const { return AttackPower; }
	float GetElementPower() const { return ElementPower; }
	float GetHealthPower() const { return HealthPower; }
	void SetIsHiden(bool IsHiden);
	TObjectPtr<UTexture2D> GetTexture() { return Texture; }
	void InitializeData();


};
