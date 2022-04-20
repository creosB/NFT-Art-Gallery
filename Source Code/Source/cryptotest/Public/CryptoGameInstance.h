// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CryptoGameInstance.generated.h"


UCLASS()
class CRYPTOTEST_API UCryptoGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UCryptoGameInstance(const FObjectInitializer& ObjectInitializer);
	
	// CREATE
	UFUNCTION(BlueprintCallable)
	void CreateSession();
	
	// DELETE
	UFUNCTION(BlueprintCallable)
	void DestroySession();

	// GET ALL FRIENDS LISTS
	UFUNCTION(BlueprintCallable)
	void GetFriendList();

	// UI
	UFUNCTION(BlueprintCallable)
	void InviteUI();
	UFUNCTION(BlueprintCallable)
	void FriendsUI();

	// AUTH
	void Login();

	// REFRESH SERVER LIST
	virtual void RefreshServerList() override;
	
	// JOIN
	virtual void Join(uint32 Index) override;
	
	// MAIN MENU
	virtual void LoadMainMenu() override;
	
	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	
	// PAUSE MENU
	UFUNCTION(BlueprintCallable)
	void PauseLoadMenu();
	
	// START SESSION
	void StartSession();

	// Check
	bool bIsLoggedIn;

private:
	// Delegates
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
	                     const FString& Error); // AUTH
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful); // DESTROY
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful); // CREATE
	void OnFindSessionsComplete(bool bWasSuccessful); // FIND
	void OnReadFriendsListsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName,
	                                const FString& ErrorStr); // GET ALL FRIENDS LISTS
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType,
	                      const FString& ErrorString);
	void OnSessionUserInviteAcceptedBase(const bool bWasSuccessful, const int32 ControllerId, FUniqueNetIdPtr UserId, const FOnlineSessionSearchResult& InviteResult);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	
	TSharedPtr<class FOnlineSessionSearch> SearchSettings; // SETTINGS

	TSubclassOf<class UUserWidget> MenuClass = nullptr;
	TSubclassOf<class UUserWidget> PauseMenuClass = nullptr;
	
	UMainMenu* Menu = nullptr;
	UPauseMenu* PauseMenu = nullptr;

	IOnlineSessionPtr SessionInterface;
	
	virtual void Init() override;

	// Host
	void Host();
protected:
	// Subsystem
	class IOnlineSubsystem* OnlineSubsystem;
};
