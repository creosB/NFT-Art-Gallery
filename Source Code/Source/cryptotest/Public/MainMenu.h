// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "ServerList.h"
#include "SettingsDataStruct.h"
#include "Engine/DataTable.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()
	// get all the server information for show some the info
	FString Name;
	uint16 CurrentPlayer;
	uint16 MaxPlayers;
	FString PingText;
};


/**
 * 
 */
UCLASS()
class CRYPTOTEST_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);
	void SelectIndex(uint32 Index);
	void RefreshList() const;
private:
	// Looks for a widget in Blueprint with the same name as the property.

	// MAIN MENU BUTTONS
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerBrowserButton; // server browser button in main menu
	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsButton; // settings button in main menu
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton; // back button in join menu

	// JOIN MENU BUTTONS
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton; // join button in join a join menu
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton; // back button in join menu

	// SETTINGS MENU BUTTONS
	UPROPERTY(meta = (BindWidget))
	class UButton* SettingsBackButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* GraphicsButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* SoundButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* ControlsButton;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* Resolution;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ViewDist;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* AntiAliasing;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ShadowQuality;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* TextureQuality;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* VsyncQuality;
	UPROPERTY(meta = (BindWidget))
	class USlider* MasterVolume;
	UPROPERTY(meta = (BindWidget))
	class USlider* MusicVolume;

	// WIDGET SWITCHER
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitch; // wrap with widget switcher on the editor
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* SettingsSwitcher;

	// WIDGETS
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu; // main menu widget
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu; // join menu widget
	UPROPERTY(meta = (BindWidget))
	class UWidget* SettingsMenu; // settings menu widget
	UPROPERTY(meta = (BindWidget))
	class UWidget* GraphicsWidget; // GraphicsWidget in settings menu
	UPROPERTY(meta = (BindWidget))
	class UWidget* ControlsWidget; // GraphicsWidget in settings menu
	UPROPERTY(meta = (BindWidget))
	class UWidget* SoundWidget; // GraphicsWidget in settings menu

	// SERVER LIST
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;
	TSubclassOf<class UUserWidget> ServerListClass = nullptr;
	
	UFUNCTION()
	void JoinServer();
	UFUNCTION()
	void OpenJoinMenu(); // when you pushed the button, it will call this func.
	UFUNCTION()
	void OpenSettingsMenu();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void Exit();
	UFUNCTION()
	void Sounds();
	UFUNCTION()
	void Graphics();
	UFUNCTION()
	void Controls();
	UFUNCTION()
	void SettingsBack();
	UFUNCTION()
	void SaveGraphicsSettings(FString sItem, ESelectInfo::Type seltype);
	UFUNCTION()
	void SaveMusicSettings(float Value);

	TOptional<uint32> SelectedIndex;
	void UpdateChildren();

	// Hover Widget functions
	UFUNCTION()
	void OnHoveredServer();
	UFUNCTION()
	void OnHoveredSettings();
	UFUNCTION()
	void OnHoveredQuit();
	UFUNCTION()
	void OnHoveredGraphics();
	UFUNCTION()
	void OnHoveredSound();
	UFUNCTION()
	void OnHoverdControls();
	UFUNCTION()
	void OnHoveredSettingsBack();

	// UnHover Widget functions
	UFUNCTION()
	void OnUnHoveredServer();
	UFUNCTION()
	void OnUnHoveredSettings();
	UFUNCTION()
	void OnUnHoveredQuit();
	UFUNCTION()
	void OnUnHoveredGraphics();
	UFUNCTION()
	void OnUnHoveredSound();
	UFUNCTION()
	void OnUnHoverdControls();
	UFUNCTION()
	void OnUnHoveredSettingsBack();

	// WIDGET ANIMATION
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* ServerAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* SettingsAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* QuitAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* GraphicsAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* ControlAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* SettingsBackAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* SoundAnim;

	// SETTINGS DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Table", meta = (AllowPrivateAccess = true))
	UDataTable* SettingsDataTable;
	TMap<FString, FIntPoint> Res;
	TMap<FString, int32> View;
	TMap<FString, int32> Aliasing;
	TMap<FString, int32> Shadow;
	TMap<FString, bool> Vsync;

	// Save Game
	class UCryptoSaveGame* SaveGameData = nullptr;
	bool IsSaved = false;

	virtual void NativeDestruct() override;
	virtual bool Initialize() override;
};
