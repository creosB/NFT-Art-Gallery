// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRYPTOTEST_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// pure virtual function - no implementation
	virtual void Join(uint32 Index) PURE_VIRTUAL(UCryptoGameInstance::Join; uint32 Index);
	virtual void LoadMainMenu() PURE_VIRTUAL(UCryptoGameInstance::LoadMainMenu);
	virtual void RefreshServerList() PURE_VIRTUAL(UCryptoGameInstance::RefreshServerList);
};
