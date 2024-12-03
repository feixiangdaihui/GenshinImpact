// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenshinImpactGameMode.h"
#include "GenshinImpactCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGenshinImpactGameMode::AGenshinImpactGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
