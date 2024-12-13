// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayCharacter.h"
#include "AdventurePlayCharacter.generated.h"
class UBoxComponent;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API AAdventurePlayCharacter : public APlayCharacter
{
	GENERATED_BODY()
public:
	AAdventurePlayCharacter();
	virtual void SpawnNormalAttack();
	virtual void SpawnCastSpell();
	//拳头碰撞体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TObjectPtr<UBoxComponent> NormalAttackCollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	float SpellRangeDia;
	UFUNCTION()
	void NormalAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
