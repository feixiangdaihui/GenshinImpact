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
