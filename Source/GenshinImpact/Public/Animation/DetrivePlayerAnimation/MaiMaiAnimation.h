// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/PlayCharacterAnimation.h"
#include "MaiMaiAnimation.generated.h"
class AMaiMaiPlayCharacter;
/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UMaiMaiAnimation : public UPlayCharacterAnimation
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	TObjectPtr<AMaiMaiPlayCharacter> SubPlayCharacter;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsNormalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsCastSpell;

	
};
