// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsDataStruct.h"
#include "GameFramework/SaveGame.h"
#include "CryptoSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTOTEST_API UCryptoSaveGame : public USaveGame
{
	
	GENERATED_BODY()
	
public:
	UCryptoSaveGame();

	UPROPERTY(VisibleAnywhere, Category = "Save Game Data")
	FSettingsDataStruct SettingsData;
};
