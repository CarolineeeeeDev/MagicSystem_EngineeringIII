// Copyright Epic Games, Inc. All Rights Reserved.

#include "MagicSystemGameMode.h"
#include "MagicSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMagicSystemGameMode::AMagicSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
