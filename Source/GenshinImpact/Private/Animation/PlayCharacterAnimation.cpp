// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayCharacterAnimation.h"
#include "Character/PlayCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayCharacterAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Speed = 0.0f;
	IsInAir = false;
	ZVelocity = 0.0f;
	PlayCharacter = Cast<APlayCharacter>(GetOwningActor());
	if (PlayCharacter)
	{
		IsCastSpell = false;
		IsNormalAttack = false;
		CharacterMovementComponent = PlayCharacter->GetCharacterMovement();
	}
}

void UPlayCharacterAnimation::NativeUpdateAnimation(float  DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayCharacter && CharacterMovementComponent)
	{
		Speed = CharacterMovementComponent->Velocity.Size();
		IsInAir = CharacterMovementComponent->IsFalling();
		ZVelocity = CharacterMovementComponent->Velocity.Z;

		IsNormalAttack = PlayCharacter->IsNormalAttack;
		IsCastSpell = PlayCharacter->IsCastingSpell;
	}
}

void UPlayCharacterAnimation::SetIsAnimForbidden(bool bIsAnimForbidden)
{
	if (PlayCharacter)
	{
		PlayCharacter->IsAnimForbidden = bIsAnimForbidden;
	}
}

void UPlayCharacterAnimation::SetIsJudgeNormalAttack(bool bIsNormalAttack)
{
	if (PlayCharacter)
	{
		PlayCharacter->IsJudgeNormalAttack = bIsNormalAttack;
	}
}


