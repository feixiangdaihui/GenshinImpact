// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayCharacter.h"
#include "IronFistGirlCharacter.generated.h"
class UBoxComponent;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API AIronFistGirlCharacter : public APlayCharacter
{
	GENERATED_BODY()
public:
	AIronFistGirlCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//拳头碰撞体
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TObjectPtr<UBoxComponent> LeftFistCollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TObjectPtr<UBoxComponent> RightFistCollisionComponent;
	


	//技能设定,攻击范围
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CastSpell")
	float SpellRangeDia;

	virtual void SpawnNormalAttack();
	virtual void SpawnCastSpell();

	UFUNCTION()
	void FistCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
