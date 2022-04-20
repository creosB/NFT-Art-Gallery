// Copyright Epic Games, Inc. All Rights Reserved.

#include "cryptotest/Public/cryptotestGameMode.h"
#include "UObject/ConstructorHelpers.h"

AcryptotestGameMode::AcryptotestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Assets/Blueprints/Character/BP_CryptoCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
