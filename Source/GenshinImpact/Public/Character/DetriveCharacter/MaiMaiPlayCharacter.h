// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayCharacter.h"
#include "MaiMaiPlayCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API AMaiMaiPlayCharacter : public APlayCharacter
{
	GENERATED_BODY()
public:
	AMaiMaiPlayCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//动作处理
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool IsCastingSpell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool IsNormalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* CastSpellAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* NormalAttackAction;
	virtual void CastSpell();
	virtual void CastSpellEnd();
	virtual void NormalAttack();
	virtual void NormalAttackEnd();



	//投射物
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileComponent> NormalAttackProjectileComponent;
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnNormalAttackProjectile();
	//普通攻击倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float NormalAttackRate;
	//技能倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float CastSpellRate;
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnCastSpell();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float CastSpellBlueCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileComponent> CastSpellProjectileComponent;



	
};
