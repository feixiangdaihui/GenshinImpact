// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalTypes/GlobalTypes.h"

GElementRestrain UGlobalTypes::GetElementRestrain(GElement self, GElement other)
{
	if (int(self) - int(other) == -1 || (self == GElement::Earth && other == GElement::Matel))
		return GElementRestrain::Positive;
	else if (int(self) - int(other) == 1 || (self == GElement::Matel && other == GElement::Earth))
		return GElementRestrain::Negative;
	else
		return GElementRestrain::Neutral;
}

float UGlobalTypes::ModifyDamage(float Damage, int EnemyLevel, int CharacterLevel, GElement EnemyElement, GElement CharacterElement)
{
	GElementRestrain RestrainState = GetElementRestrain(EnemyElement, CharacterElement);
	int LevelDifference = (EnemyLevel - CharacterLevel) > 0 ? 0 : (EnemyLevel - CharacterLevel);
	float LevelModify = 1 - LevelDifference * LEVELMODIFY;
	Damage = Damage * LevelModify;
	switch (RestrainState)
	{
	case GElementRestrain::Positive:
		return Damage * ELEMENTRESTRAINPOSITIVE;
	case GElementRestrain::Negative:
		return Damage * ELEMENTRESTRAINNEGATIVE;
	case GElementRestrain::Neutral:
		return Damage;
	}
	return 0;
}
