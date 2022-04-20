// Fill out your copyright notice in the Description page of Project Settings.


#include "CryptoGameInstance.h"

#include "cryptotestCharacter.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineExternalUIInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "CryptoSaveGame.h"

const FName SESSION_NAME = TEXT("Session");
//const FName SERVER_NAME_SETTINGS_KEY = TEXT("ArtGallery");

UCryptoGameInstance::UCryptoGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// find menu widget class and define to MenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Assets/Blueprints/Widgets/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	// find pause menu widget class and define to PauseMenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(
		TEXT("/Game/Assets/Blueprints/Widgets/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr)) return;
	PauseMenuClass = PauseMenuBPClass.Class;
	//UE_LOG(LogTemp, Warning, TEXT("Game Instance Constructor"));

	bIsLoggedIn = false;
}

void UCryptoGameInstance::Init()
{
	Super::Init();
	OnlineSubsystem = IOnlineSubsystem::Get(); // GET Online Subsystem

	if (OnlineSubsystem != nullptr)
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();
	}

	Login();
	
	// When server shutdown
	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UCryptoGameInstance::OnNetworkFailure);
	}
}


// Login function
void UCryptoGameInstance::Login()
{
	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			FOnlineAccountCredentials Credentials;

			if(!IsDedicatedServerInstance())
			{
				Credentials.Id = FString();
				Credentials.Token = FString();
				Credentials.Type = FString("accountportal");
			}
			/*
						// DEVELOPER LOGIN
						Credentials.Id = FString("127.0.0.1:8081"); // AUTH_LOGIN
						Credentials.Token = FString("CreosCred"); // AUTH password
						// you can use accountportal or developer - you can set other tags -
						Credentials.Type = FString("developer"); // AUTH_TYPE
			
			*/
			Identity->OnLoginCompleteDelegates->AddUObject(this, &UCryptoGameInstance::OnLoginComplete);
			Identity->Login(0, Credentials);
		}
	}
}

// Login function delegate
void UCryptoGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                          const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("LoggedIn Result: %d"), bWasSuccessful); // check login

	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			// set login info
			switch (Identity->GetLoginStatus(0))
			{
			case ELoginStatus::LoggedIn: bIsLoggedIn = true;
				if (IsDedicatedServerInstance())
				{
					Host();
				}
				break;
			case ELoginStatus::NotLoggedIn: bIsLoggedIn = false;
				break;
			default: bIsLoggedIn = false;
			}

			// // it will delete delegates when it completed.
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
}

// Create Session Function
void UCryptoGameInstance::CreateSession()
{
	if (OnlineSubsystem && bIsLoggedIn)
	{
		// Get SessionInterface function from subsystem
		if (SessionInterface)
		{
			FOnlineSessionSettings SessionSettings;

			// Default Settings
			SessionSettings.bShouldAdvertise = true; // for invite your friend
			SessionSettings.bIsDedicated = true;
			SessionSettings.bIsLANMatch = true; // local gameplay is true
			SessionSettings.NumPublicConnections = 5; // how many people can join the your lobby // this is limit
			SessionSettings.NumPrivateConnections = 5; // how many people can join the your lobby // this is limit
			SessionSettings.bAllowJoinInProgress = true; // join permission
			SessionSettings.bAllowJoinViaPresence = true; // join permission
			SessionSettings.bUsesPresence = true;
			SessionSettings.bUseLobbiesIfAvailable = true;
			SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings.bAllowInvites = true;

			// Set and create lobby info
			// You can check with "SEARCHKEYWORDS" attribute  key at lobbies section.
			SessionSettings.Set(SEARCH_KEYWORDS, FString("GalleryLobby"),
			                    EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

			// Define the delegate
			SessionInterface->OnCreateSessionCompleteDelegates.
			                  AddUObject(this, &UCryptoGameInstance::OnCreateSessionComplete);

			// Create session
			SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
		}
	}
}

// Create Session Delegate
void UCryptoGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Create Success: %d"), bWasSuccessful);

	if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session is not created"));
		return;
	}

	// it will check is logged in and subsystem is not nullptr
	if (OnlineSubsystem) // bIsLoggedIn && 
	{
		if (SessionInterface.IsValid())
		// Get SessionInterface function from subsystem
		{
			if (bWasSuccessful)
			{
				// Define the delegate
				SessionInterface->OnStartSessionCompleteDelegates.
				                  AddUObject(this, &UCryptoGameInstance::OnStartSessionComplete);

				// Set the StartSession delegate handle
				StartSession();
			}
			// it will delete delegates when it completed.
			SessionInterface->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("You can't create session: Not Logged In %d"), bWasSuccessful);
	}
}


// Destroy Session Function
void UCryptoGameInstance::DestroySession()
{
	if (OnlineSubsystem)
	{
		// Get SessionInterface function from subsystem
		if (SessionInterface)
		{
			// define the delegate
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(
				this, &UCryptoGameInstance::OnDestroySessionComplete);
			// it will destroy session.
			SessionInterface->DestroySession(SESSION_NAME);
		}
	}
}

// Destroy Session Delegate
void UCryptoGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSubsystem)
	{
		// Get SessionInterface function from subsystem
		if (SessionInterface)
		{
			// it will delete delegates when it completed.
			SessionInterface->ClearOnDestroySessionCompleteDelegates(this);
		}
	}
}

// add new server and clear old server list
void UCryptoGameInstance::RefreshServerList()
{
	if (OnlineSubsystem)
	{
		if (SessionInterface.IsValid())
		{
			// Find Online Session
			// MakeShareable c++ pointer convert to reference pointer
			SearchSettings = MakeShareable(new FOnlineSessionSearch()); // heap memory
			// check is it null
			if (SearchSettings.IsValid())
			{
				SearchSettings = MakeShareable(new FOnlineSessionSearch()); // create new reference
				SearchSettings->MaxSearchResults = 100;
				SearchSettings->bIsLanQuery = false;
				SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, true, EOnlineComparisonOp::Equals);

				// define the delegate
				SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(
					this, &UCryptoGameInstance::OnFindSessionsComplete);

				ULocalPlayer* const Player = GetFirstGamePlayer();
				// Find session
				SessionInterface->FindSessions(Player->GetUniqueID(), SearchSettings.ToSharedRef());
				// get settings ref and find session
			}
		}
	}
}

// Find Session Delegate
void UCryptoGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (bWasSuccessful && SearchSettings.IsValid() && Menu != nullptr)
	{
		TArray<FServerData> ServerNames; // server name array

		for (const FOnlineSessionSearchResult& SearchResult : SearchSettings->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session name: %s"), *SearchResult.GetSessionIdStr());
			FServerData Data;
			//Data.Name = SearchResult.GetSessionIdStr(); set server name with search result
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections; // get max player number
			Data.CurrentPlayer = 1 + (Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections);
			Data.PingText = FString::FromInt(SearchResult.PingInMs);
			// get current player number
			// Set server name
			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(SEARCH_KEYWORDS, ServerName))
			{
				UE_LOG(LogTemp, Warning, TEXT("Data Found in Settings %s"), *ServerName);
				Data.Name = ServerName; // set server name with input name
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Didn't get the expected ata"));
				Data.Name = "Could not find name";
			}
			// add every result on the list
			ServerNames.Add(Data); // add the struct
		}
		Menu->SetServerList(ServerNames); // return to the list on menu

		// it will delete delegates when it completed.
		SessionInterface->ClearOnFindSessionsCompleteDelegates(this);
		//UE_LOG(LogTemp, Warning, TEXT("Found Sessions: %d"), SearchSettings->SearchResults.Num()); // check
	}
}

// join session
void UCryptoGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) { return; }
	if (!SearchSettings.IsValid()) { return; }
	if (Menu != nullptr)
	{
		// it's sending server list to MainMenu function.
		//Menu->SetServerList({"Test1", "Test2", "Test3", "Test4"});
	}
	UE_LOG(LogTemp, Warning, TEXT("Joinning Session"));
	// define the delegate
	SessionInterface->OnJoinSessionCompleteDelegates.
	                  AddUObject(this, &UCryptoGameInstance::OnJoinSessionComplete);

	SessionInterface->JoinSession(0, SESSION_NAME, SearchSettings->SearchResults[Index]);
}

// Join Session Delegate
void UCryptoGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
	// Get SessionInterface function from subsystem
	UE_LOG(LogTemp, Warning, TEXT("Join Session Delegate is working!"));
	if (OnlineSubsystem)
	{
		if (SessionInterface)
		{
			FString ConnectionInfo;
			if (!SessionInterface->GetResolvedConnectString(SessionName, ConnectionInfo)) // get connection info
			{
				UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."));
				return;
			}
			// join to the input adress.
			APlayerController* PlayerController = GetFirstLocalPlayerController();
			if (!ensure(PlayerController != nullptr)) { return; }
			PlayerController->ClientTravel(ConnectionInfo, ETravelType::TRAVEL_Absolute); // travel the map

			UE_LOG(LogTemp, Warning, TEXT("Player is travelling"));
		}
	}
}

// when start session
void UCryptoGameInstance::StartSession()
{
	if (SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Session is start function working..."));
		SessionInterface->StartSession(SESSION_NAME);
	}
}

// Start session delegate
void UCryptoGameInstance::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSubsystem)
	{
		if (SessionInterface.IsValid())
		{
			// load to the map
			UWorld* World = GetWorld();
			if (!ensure(World != nullptr)) { return; }
			if (AGameModeBase* GameModeBase = Cast<AGameModeBase>(UGameplayStatics::GetGameMode(World)))
			{
				if (bWasSuccessful)
				{
					UE_LOG(LogTemp, Warning, TEXT("Session is starting..."));
					GameModeBase->bUseSeamlessTravel = true;
					World->ServerTravel(TEXT("/Game/Maps/ArtGallery?listen"));
				}
			}

			SessionInterface->ClearOnStartSessionCompleteDelegates(this);
		}
	}
}

// Host for dedicated server
void UCryptoGameInstance::Host()
{
	if (SessionInterface.IsValid() && bIsLoggedIn)
	{
		// auto guess which type and get session
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		// check session is null or not
		if (ExistingSession != nullptr)
		{
			// destroy session
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("I'm creating session"));
			// create session
			CreateSession();
		}
	}
}

// Get All Friends Lists function
void UCryptoGameInstance::GetFriendList()
{
	if (bIsLoggedIn && OnlineSubsystem)
	{
		if (IOnlineFriendsPtr Friends = OnlineSubsystem->GetFriendsInterface())
		{
			Friends->ReadFriendsList(0, FString(""),
			                         FOnReadFriendsListComplete::CreateUObject(
				                         this, &UCryptoGameInstance::OnReadFriendsListsComplete));
		}
	}
}

// Get All Friends Lists Delegate
void UCryptoGameInstance::OnReadFriendsListsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName,
                                                     const FString& ErrorStr)
{
	if (bWasSuccessful && OnlineSubsystem)
	{
		if (IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface())
		{
			TArray<TSharedRef<FOnlineFriend>> FriendsLists; // friend list reference
			if (FriendsPtr->GetFriendsList(0, ListName, FriendsLists)) // get all friends lists
			{
				for (TSharedRef<FOnlineFriend> Friend : FriendsLists) // find all friend from friendlists
				{
					FString FriendName = Friend.Get().GetRealName();

					UE_LOG(LogTemp, Warning, TEXT("Friend Name: %s"), *FriendName); // check
				}
			}
		}
	}
}

// Show Invite UI
void UCryptoGameInstance::InviteUI()
{
	if (bIsLoggedIn && OnlineSubsystem)
	{
		if (IOnlineExternalUIPtr ExternalUI = OnlineSubsystem->GetExternalUIInterface())
		{
			ExternalUI->ShowInviteUI(0, SESSION_NAME); // invite UI
		}
	}
}

// Show Friends List UI function
void UCryptoGameInstance::FriendsUI()
{
	if (bIsLoggedIn && OnlineSubsystem)
	{
		if (IOnlineExternalUIPtr ExternalUI = OnlineSubsystem->GetExternalUIInterface())
		{
			ExternalUI->ShowFriendsUI(0); // friend UI
		}
	}
}

// When server shutdown it will load main menu
void UCryptoGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType,
                                           const FString& ErrorString)
{
	// when host left the server, load the main menu
	LoadMainMenu();
}


// create main menu widget
void UCryptoGameInstance::LoadMenu()
{
	// Create menu widget
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass); // create menu widget with MenuClass
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup(); // add to viewport and show cursor
	Menu->SetMenuInterface(this);
}


// create pause menu widget
void UCryptoGameInstance::PauseLoadMenu()
{
	if (!ensure(PauseMenuClass != nullptr)) return;
	PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass); // create menu widget with MenuClass
	if (!ensure(PauseMenu != nullptr)) { return; }
	PauseMenu->Setup(); // add to viewport and show cursor
	PauseMenu->SetMenuInterface(this);
}

// open the main menu
void UCryptoGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) { return; }
	PlayerController->ClientTravel("/Game/Maps/Lobby", ETravelType::TRAVEL_Absolute); // return to the main menu
}

void UCryptoGameInstance::OnSessionUserInviteAcceptedBase(const bool bWasSuccessful, const int32 ControllerId,
                                                          FUniqueNetIdPtr UserId,
                                                          const FOnlineSessionSearchResult& InviteResult)
{
	if (OnlineSubsystem && bWasSuccessful)
	{
		SessionInterface->JoinSession(0, SESSION_NAME, SearchSettings->SearchResults[0]);
	}
}
