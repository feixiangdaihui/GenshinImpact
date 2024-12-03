// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DetrivePlayerAnimation/MaiMaiAnimation.h"
#include "Character/DetriveCharacter/MaiMaiPlayCharacter.h"
void UMaiMaiAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	IsCastSpell = false;
	IsNormalAttack = false;
	SubPlayCharacter = Cast<AMaiMaiPlayCharacter>(GetOwningActor());
}

void UMaiMaiAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (SubPlayCharacter )
	{
		IsNormalAttack = SubPlayCharacter->IsNormalAttack;
		IsCastSpell = SubPlayCharacter->IsCastingSpell;
	}
}
