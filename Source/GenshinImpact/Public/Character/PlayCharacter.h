// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenshinImpact/GenshinImpactCharacter.h"
#include "Interface/HealthInterface.h"
#include "PlayCharacter.generated.h"

class UHealthComponent;
class UProjectileComponent;
class UBlueComponent;
/**
 *
 */
UCLASS()
class GENSHINIMPACT_API APlayCharacter : public AGenshinImpactCharacter, public IHealthInterface
{
    GENERATED_BODY()

public:

    APlayCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//处理输入

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    bool IsAnimForbidden;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float Speed;
	virtual void Move(const FInputActionValue& Value);

	//组件
    //血量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;
	virtual void TakeDamageByValue_Implementation(float DamageAmount) override;
	virtual void Die_Implementation() override;

	//蓝量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlueComponent> BlueComponent;
	UPROPERTY(EditAnywhere, Category = "Blue")
	float CastSpellBlueCost;
	void RecoverBlueByTick();


};
