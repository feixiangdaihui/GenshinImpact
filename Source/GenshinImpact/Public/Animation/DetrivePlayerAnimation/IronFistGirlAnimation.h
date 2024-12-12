// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/PlayCharacterAnimation.h"
#include "IronFistGirlAnimation.generated.h"

/**
 * 
 */
UCLASS()
class GENSHINIMPACT_API UIronFistGirlAnimation : public UPlayCharacterAnimation
{
	GENERATED_BODY()
public:


	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
};
