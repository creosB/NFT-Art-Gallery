#include "MainMenu.h"

#include "CryptoSaveGame.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	// find menu widget class and define to MenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> ServerListBPClass(
		TEXT("/Game/Assets/Blueprints/Widgets/WBP_ServerList"));
	if (!ensure(ServerListBPClass.Class != nullptr)) return;
	ServerListClass = ServerListBPClass.Class;

	SaveGameData = Cast<UCryptoSaveGame>(UGameplayStatics::LoadGameFromSlot("CryptoGameSlot", 0));

	if (SaveGameData != nullptr)
	{
		// check save
		/*
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameData->SettingsData.AntiAliasing);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameData->SettingsData.ScreenResolution);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameData->SettingsData.TextureQuality);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameData->SettingsData.ShadowQuality);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameData->SettingsData.VsyncQuality);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SaveGameData->SettingsData.ViewDistance);
		UE_LOG(LogTemp, Warning, TEXT("%f"), SaveGameData->SettingsData.MusicVolume);
		UE_LOG(LogTemp, Warning, TEXT("%f"), SaveGameData->SettingsData.MasterVolume); */
	}
	else
	{
		// couldn't load save game
		SaveGameData = Cast<
			UCryptoSaveGame>(UGameplayStatics::CreateSaveGameObject(UCryptoSaveGame::StaticClass()));
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	// MAIN MENU
	if (!ensure(ServerBrowserButton != nullptr)) { return false; }
	ServerBrowserButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	ServerBrowserButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredServer);
	ServerBrowserButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredServer);
	if (!ensure(SettingsButton != nullptr)) { return false; }
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSettingsMenu);
	SettingsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredSettings);
	SettingsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredSettings);
	if (!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Exit);
	QuitButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredQuit);
	QuitButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredQuit);

	// JOIN MENU
	if (!ensure(JoinButton != nullptr)) { return false; }
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	if (!ensure(BackButton != nullptr)) { return false; }
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	// SETTINGS MENU
	if (!ensure(GraphicsButton != nullptr)) { return false; }
	GraphicsButton->OnClicked.AddDynamic(this, &UMainMenu::Graphics);
	GraphicsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredGraphics);
	GraphicsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredGraphics);
	if (!ensure(SoundButton != nullptr)) { return false; }
	SoundButton->OnClicked.AddDynamic(this, &UMainMenu::Sounds);
	SoundButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredSound);
	SoundButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredSound);
	if (!ensure(ControlsButton != nullptr)) { return false; }
	ControlsButton->OnClicked.AddDynamic(this, &UMainMenu::Controls);
	ControlsButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoverdControls);
	ControlsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoverdControls);
	if (!ensure(SettingsBackButton != nullptr)) { return false; }
	SettingsBackButton->OnClicked.AddDynamic(this, &UMainMenu::SettingsBack);
	SettingsBackButton->OnHovered.AddDynamic(this, &UMainMenu::OnHoveredSettingsBack);
	SettingsBackButton->OnUnhovered.AddDynamic(this, &UMainMenu::OnUnHoveredSettingsBack);

	if (!ensure(Resolution != nullptr)) { return false; }
	Resolution->OnSelectionChanged.AddDynamic(this, &UMainMenu::SaveGraphicsSettings);
	Resolution->SetSelectedOption(SaveGameData->SettingsData.ScreenResolution);
	if (!ensure(ViewDist != nullptr)) { return false; }
	ViewDist->OnSelectionChanged.AddDynamic(this, &UMainMenu::SaveGraphicsSettings);
	ViewDist->SetSelectedOption(SaveGameData->SettingsData.ViewDistance);
	if (!ensure(AntiAliasing != nullptr)) { return false; }
	AntiAliasing->OnSelectionChanged.AddDynamic(this, &UMainMenu::SaveGraphicsSettings);
	AntiAliasing->SetSelectedOption(SaveGameData->SettingsData.AntiAliasing);
	if (!ensure(ShadowQuality != nullptr)) { return false; }
	ShadowQuality->OnSelectionChanged.AddDynamic(this, &UMainMenu::SaveGraphicsSettings);
	ShadowQuality->SetSelectedOption(SaveGameData->SettingsData.ShadowQuality);
	if (!ensure(TextureQuality != nullptr)) { return false; }
	TextureQuality->OnSelectionChanged.AddDynamic(this, &UMainMenu::SaveGraphicsSettings);
	TextureQuality->SetSelectedOption(SaveGameData->SettingsData.TextureQuality);
	if (!ensure(VsyncQuality != nullptr)) { return false; }
	VsyncQuality->OnSelectionChanged.AddDynamic(this, &UMainMenu::SaveGraphicsSettings);
	VsyncQuality->SetSelectedOption(SaveGameData->SettingsData.VsyncQuality);
	if (!ensure(MasterVolume != nullptr)) { return false; }
	MasterVolume->OnValueChanged.AddDynamic(this, &UMainMenu::SaveMusicSettings);
	MasterVolume->SetValue(SaveGameData->SettingsData.MasterVolume);
	if (!ensure(MusicVolume != nullptr)) { return false; }
	MusicVolume->OnValueChanged.AddDynamic(this, &UMainMenu::SaveMusicSettings);
	MusicVolume->SetValue(SaveGameData->SettingsData.MusicVolume);

	return true;
}

// Get all server names from game instance
void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
	// call world
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) { return; }

	// Clear old server list
	RefreshList();

	// server index
	uint32 i = 0;

	// it will add every server name.
	for (const FServerData& ServerData : ServerNames)
	{
		// it will create ServerListWidget child to ScrollBox
		UServerList* ServerListWidget = CreateWidget<UServerList>(this, ServerListClass);
		// create ServerList widget with ServerListClass
		if (!ensure(ServerListWidget != nullptr)) { return; }

		ServerListWidget->ServerName->SetText(FText::FromString(ServerData.Name));
		ServerListWidget->PingText->SetText(FText::FromString(ServerData.PingText + " ms"));

		/*	ServerListWidget->PlayerNumber->SetText(
				FText::FromString(
					FString::FromInt(ServerData.CurrentPlayer) + "/" + FString::FromInt(ServerData.MaxPlayers))); */
		ServerListWidget->Setup(this, i);
		++i;
		ServerList->AddChild(ServerListWidget); // add to scroll box
	}
}

// when you choose one server, it will get the selected index
void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
	{
		auto List = Cast<UServerList>(ServerList->GetChildAt(i));
		if (List != nullptr)
		{
			List->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

// Clear old server list
void UMainMenu::RefreshList() const
{
	ServerList->ClearChildren();
}

// connect - join the server
void UMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && MainMenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
		// Return selected index value to game instance
		MainMenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index not set"));
	}
}


// switch between main menu
void UMainMenu::OpenJoinMenu()
{
	if (!ensure(WidgetSwitch != nullptr)) { return; }
	if (!ensure(JoinMenu != nullptr)) { return; }

	// you can active this method (it's safety) or you can active with widget index.
	WidgetSwitch->SetActiveWidget(JoinMenu);

	// when it switched the widget, it will call the refresh func.
	if (MainMenuInterface != nullptr) { MainMenuInterface->RefreshServerList(); }
}

// switch between settings Menu
void UMainMenu::OpenSettingsMenu()
{
	if (!ensure(WidgetSwitch != nullptr)) { return; }
	if (!ensure(SettingsMenu != nullptr)) { return; }

	// you can active this method (it's safety) or you can active with widget index.
	WidgetSwitch->SetActiveWidget(SettingsMenu);
}

// switch between Main Menu
void UMainMenu::OpenMainMenu()
{
	if (!ensure(WidgetSwitch != nullptr)) { return; }
	if (!ensure(MainMenu != nullptr)) { return; }

	// you can active this method (it's safety) or you can active with widget index.
	WidgetSwitch->SetActiveWidget(MainMenu);
}

// Exit to the game
void UMainMenu::Exit()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	PlayerController = World->GetFirstPlayerController(); // call player controller
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}


// Settings Menu
void UMainMenu::Graphics()
{
	if (!ensure(SettingsSwitcher != nullptr)) { return; }

	SettingsSwitcher->SetActiveWidget(GraphicsWidget);
}

void UMainMenu::Controls()
{
	if (!ensure(SettingsSwitcher != nullptr)) { return; }

	SettingsSwitcher->SetActiveWidget(ControlsWidget);
}

void UMainMenu::Sounds()
{
	if (!ensure(SettingsSwitcher != nullptr)) { return; }
	SettingsSwitcher->SetActiveWidget(SoundWidget);
}

void UMainMenu::SettingsBack()
{
	if (!ensure(WidgetSwitch != nullptr)) { return; }
	if (!ensure(MainMenu != nullptr)) { return; }

	if (IsSaved)
	{
		UGameplayStatics::SaveGameToSlot(SaveGameData, "CryptoGameSlot", 0);
	}

	WidgetSwitch->SetActiveWidget(MainMenu);
	IsSaved = false;
}


// On Hovered Functions
void UMainMenu::OnHoveredServer()
{
	if (ServerAnim)
	{
		PlayAnimation(ServerAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoveredSettings()
{
	if (SettingsAnim)
	{
		PlayAnimation(SettingsAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoveredGraphics()
{
	if (GraphicsAnim)
	{
		PlayAnimation(GraphicsAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoverdControls()
{
	if (ControlAnim)
	{
		PlayAnimation(ControlAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoveredSound()
{
	if (SoundAnim)
	{
		PlayAnimation(SoundAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}

void UMainMenu::OnHoveredSettingsBack()
{
	if (SettingsBackAnim)
	{
		PlayAnimation(SettingsBackAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
	}
}


// On UnHovered Functions
void UMainMenu::OnUnHoveredServer()
{
	if (ServerAnim)
	{
		PlayAnimation(ServerAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UMainMenu::OnUnHoveredSettings()
{
	if (SettingsAnim)
	{
		PlayAnimation(SettingsAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UMainMenu::OnUnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
	}
}

void UMainMenu::OnUnHoveredGraphics()
{
	if (GraphicsAnim)
	{
		PlayAnimation(GraphicsAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}

void UMainMenu::OnUnHoveredSound()
{
	if (SoundAnim)
	{
		PlayAnimation(SoundAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}

void UMainMenu::OnUnHoverdControls()
{
	if (ControlAnim)
	{
		PlayAnimation(ControlAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}

void UMainMenu::OnUnHoveredSettingsBack()
{
	if (SettingsBackAnim)
	{
		PlayAnimation(SettingsBackAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}


void UMainMenu::SaveGraphicsSettings(FString sItem, ESelectInfo::Type seltype)
{
	if (Resolution->IsOpen())
	{
		if (SaveGameData && sItem != SaveGameData->SettingsData.ScreenResolution)
		{
			if (Res.Num() <= 0)
			{
				Res.Add(TEXT("2560x1440"), FIntPoint(2560, 1440));
				Res.Add(TEXT("1920x1080"), FIntPoint(1920, 1080));
				Res.Add(TEXT("1280x720"), FIntPoint(1280, 720));
				Res.Add(TEXT("720x480"), FIntPoint(720, 480));
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetScreenResolution(Res.FindRef(sItem));
			}
			IsSaved = true;
			SaveGameData->SettingsData.ScreenResolution = sItem;
		}
	}
	else if (ViewDist->IsOpen())
	{
		if (SaveGameData && sItem != SaveGameData->SettingsData.ViewDistance)
		{
			if (View.Num() <= 0)
			{
				View.Add("Far", 3);
				View.Add("Medium", 2);
				View.Add("Near", 1);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetViewDistanceQuality(View.FindRef(sItem));
			}
			IsSaved = true;
			SaveGameData->SettingsData.ViewDistance = sItem;
		}
	}
	else if (AntiAliasing->IsOpen())
	{
		if (SaveGameData && sItem != SaveGameData->SettingsData.AntiAliasing)
		{
			if (Aliasing.Num() <= 0)
			{
				Aliasing.Add(TEXT("Epic"), 3);
				Aliasing.Add(TEXT("High"), 2);
				Aliasing.Add(TEXT("Medium"), 1);
				Aliasing.Add(TEXT("Low"), 0);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetAntiAliasingQuality(Aliasing.FindRef(sItem));
			}
			IsSaved = true;
			SaveGameData->SettingsData.AntiAliasing = sItem;
		}
	}
	else if (ShadowQuality->IsOpen())
	{
		if (SaveGameData && sItem != SaveGameData->SettingsData.ShadowQuality)
		{
			if (Shadow.Num() <= 0)
			{
				Shadow.Add(TEXT("Ultra"), 3);
				Shadow.Add(TEXT("High"), 2);
				Shadow.Add(TEXT("Medium"), 1);
				Shadow.Add(TEXT("Low"), 0);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetShadowQuality(Shadow.FindRef(sItem));
			}
			IsSaved = true;
			SaveGameData->SettingsData.ShadowQuality = sItem;
		}
	}
	else if (TextureQuality->IsOpen())
	{
		if (SaveGameData && sItem != SaveGameData->SettingsData.TextureQuality)
		{
			// same key and value with shadow quality
			if (Shadow.Num() <= 0)
			{
				Shadow.Add(TEXT("Ultra"), 3);
				Shadow.Add(TEXT("High"), 2);
				Shadow.Add(TEXT("Medium"), 1);
				Shadow.Add(TEXT("Low"), 0);
			}
			if (GEngine)
			{
				//	UE_LOG(LogTemp, Warning, TEXT("%d"), Shadow.FindRef(sItem));
				GEngine->GameUserSettings->SetTextureQuality(Shadow.FindRef(sItem));
			}
			IsSaved = true;
			SaveGameData->SettingsData.TextureQuality = sItem;
		}
	}
	else if (VsyncQuality->IsOpen())
	{
		if (SaveGameData && sItem != SaveGameData->SettingsData.VsyncQuality)
		{
			if (Vsync.Num() <= 0)
			{
				Vsync.Add(TEXT("on"), true);
				Vsync.Add(TEXT("off"), false);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetVSyncEnabled(Vsync.FindRef(sItem));
			}
			IsSaved = true;
			SaveGameData->SettingsData.VsyncQuality = sItem;
		}
	}
}

void UMainMenu::SaveMusicSettings(float Value)
{
	if (MasterVolume)
	{
		if (SaveGameData && Value != SaveGameData->SettingsData.MasterVolume)
		{
			SaveGameData->SettingsData.MasterVolume = Value;
			IsSaved = true;
		}
	}
	else if (MusicVolume)
	{
		if (SaveGameData && Value != SaveGameData->SettingsData.MusicVolume)
		{
			SaveGameData->SettingsData.MusicVolume = Value;
			IsSaved = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unknown Settings Changed"));
	}
}


void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	// MAIN MENU
	ServerBrowserButton->OnClicked.RemoveAll(this);
	ServerBrowserButton->OnHovered.RemoveAll(this);
	ServerBrowserButton->OnUnhovered.RemoveAll(this);
	SettingsButton->OnClicked.RemoveAll(this);
	SettingsButton->OnHovered.RemoveAll(this);
	SettingsButton->OnUnhovered.RemoveAll(this);
	QuitButton->OnClicked.RemoveAll(this);
	QuitButton->OnHovered.RemoveAll(this);
	QuitButton->OnUnhovered.RemoveAll(this);

	// JOIN MENU
	JoinButton->OnClicked.RemoveAll(this);
	BackButton->OnClicked.RemoveAll(this);

	// SETTINGS MENU
	GraphicsButton->OnClicked.RemoveAll(this);
	GraphicsButton->OnHovered.RemoveAll(this);;
	GraphicsButton->OnHovered.RemoveAll(this);
	SoundButton->OnClicked.RemoveAll(this);
	SoundButton->OnHovered.RemoveAll(this);
	SoundButton->OnUnhovered.RemoveAll(this);
	ControlsButton->OnClicked.RemoveAll(this);
	ControlsButton->OnHovered.RemoveAll(this);
	ControlsButton->OnUnhovered.RemoveAll(this);
	SettingsBackButton->OnClicked.RemoveAll(this);
	SettingsBackButton->OnHovered.RemoveAll(this);
	SettingsBackButton->OnUnhovered.RemoveAll(this);
	
	// SAVE SETTINGS
	Resolution->OnSelectionChanged.RemoveAll(this);
	ViewDist->OnSelectionChanged.RemoveAll(this);
	AntiAliasing->OnSelectionChanged.RemoveAll(this);
	ShadowQuality->OnSelectionChanged.RemoveAll(this);
	TextureQuality->OnSelectionChanged.RemoveAll(this);
	VsyncQuality->OnSelectionChanged.RemoveAll(this);
	MasterVolume->OnValueChanged.RemoveAll(this);
	MusicVolume->OnValueChanged.RemoveAll(this);
}
