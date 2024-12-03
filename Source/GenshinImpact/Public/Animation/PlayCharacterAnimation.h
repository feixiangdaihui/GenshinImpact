// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Delegates/DelegateCombinations.h"

#include "PlayCharacterAnimation.generated.h"

class UCharacterMovementComponent;
class APlayCharacter;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UPlayCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY( BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	TObjectPtr<APlayCharacter> PlayCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsInAir;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ZVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsNormalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsCastSpell;


	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetIsAnimForbidden(bool bIsAnimForbidden);
};
