// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuSubsystemSteamGameMode.h"
#include "MenuSubsystemSteamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMenuSubsystemSteamGameMode::AMenuSubsystemSteamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
