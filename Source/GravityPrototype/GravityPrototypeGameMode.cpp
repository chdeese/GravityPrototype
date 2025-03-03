// Copyright Epic Games, Inc. All Rights Reserved.

#include "GravityPrototypeGameMode.h"
#include "GravityPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGravityPrototypeGameMode::AGravityPrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
