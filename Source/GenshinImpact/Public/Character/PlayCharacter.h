// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenshinImpact/GenshinImpactCharacter.h"
#include "Interface/HealthInterface.h"
#include "PlayCharacter.generated.h"

class UHealthComponent;
class UProjectileComponent;
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
    bool IsCastingSpell;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    bool IsNormalAttack;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    bool IsAnimForbidden;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float Speed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* CastSpellAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputAction* NormalAttackAction;
    void CastSpell();
	void CastSpellEnd();
    void NormalAttack();
	void NormalAttackEnd();
	virtual void Move(const FInputActionValue& Value);

	//组件
    //血量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;
	virtual void TakeDamageByValue_Implementation(float DamageAmount) override;
	virtual void Die_Implementation() override;
	//投射物
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))  
	TObjectPtr<UProjectileComponent> NormalAttackProjectileComponent;
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnNormalAttackProjectile();
    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void SpawnCastSpell();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileComponent> CastSpellProjectileComponent;


};
