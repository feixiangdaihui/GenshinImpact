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

	//投射物
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileComponent> NormalAttackProjectileComponent;
	virtual void SpawnNormalAttack();
	virtual void SpawnCastSpell();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackMode", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileComponent> CastSpellProjectileComponent;



	
};
