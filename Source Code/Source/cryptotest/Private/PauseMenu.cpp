// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }
	
	if (!ensure(CancelButton != nullptr)) { return false; }
	MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::MainMenu);
	MainMenuButton->OnHovered.AddDynamic(this, &UPauseMenu::OnHoveredMainMenu);
	MainMenuButton->OnUnhovered.AddDynamic(this, &UPauseMenu::OnUnHoveredMainMenu);
	if (!ensure(CancelButton != nullptr)) { return false; }
	CancelButton->OnClicked.AddDynamic(this, &UPauseMenu::Cancel);
	CancelButton->OnHovered.AddDynamic(this, &UPauseMenu::UPauseMenu::OnHoveredCancel);
	CancelButton->OnUnhovered.AddDynamic(this, &UPauseMenu::UPauseMenu::OnUnHoveredCancel);
	if (!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::Quit);
	QuitButton->OnHovered.AddDynamic(this, &UPauseMenu::OnHoveredQuit);
	QuitButton->OnUnhovered.AddDynamic(this, &UPauseMenu::OnUnHoveredQuit);

	return true;
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (Pause)
	{
		PlayAnimation(Pause, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.8f, false);
	}
}


// OnClick
void UPauseMenu::MainMenu()
{
	if(MainMenuInterface != nullptr)
	{
		OnLevelRemovedFromWorld(GetWorld()->GetCurrentLevel(),GetWorld()); // show main menu widget and set cursor
		MainMenuInterface->LoadMainMenu(); // travel to the main menu map
	}
}
void UPauseMenu::Quit()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), Player, EQuitPreference::Quit,true);
}
void UPauseMenu::Cancel()
{
	if(Pause)
	{
		this->PlayAnimation(Pause, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f, false);
		GetWorld()->GetTimerManager().SetTimer(AnimTimer, this, &UPauseMenu::OnClosed, 1.0f, false, Pause->GetEndTime());
	}
}


// On Hovered
void UPauseMenu::OnHoveredMainMenu()
{
	if (MainMenuAnim)
	{
		PlayAnimation(MainMenuAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.5f, false);
	}
}
void UPauseMenu::OnHoveredCancel()
{
	if (CancelAnim)
	{
		PlayAnimation(CancelAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.5f, false);
	}
}
void UPauseMenu::OnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.5f, false);
	}
}


// On UnHovered
void UPauseMenu::OnUnHoveredMainMenu()
{
	if (MainMenuAnim)
	{
		PlayAnimation(MainMenuAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}
void UPauseMenu::OnUnHoveredCancel()
{
	if (CancelAnim)
	{
		PlayAnimation(CancelAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}
void UPauseMenu::OnUnHoveredQuit()
{
	if (QuitAnim)
	{
		PlayAnimation(QuitAnim, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.5f, false);
	}
}

void UPauseMenu::OnClosed()
{
	GetWorld()->GetTimerManager().ClearTimer(AnimTimer);
	OnLevelRemovedFromWorld(GetWorld()->GetCurrentLevel(),GetWorld()); // clear viewport and get controller
}

void UPauseMenu::NativeDestruct()
{
	Super::NativeDestruct();

	MainMenuButton->OnClicked.RemoveAll(this);
	MainMenuButton->OnHovered.RemoveAll(this);
	MainMenuButton->OnUnhovered.RemoveAll(this);
	CancelButton->OnClicked.RemoveAll(this);
	CancelButton->OnHovered.RemoveAll(this);
	CancelButton->OnUnhovered.RemoveAll(this);
	QuitButton->OnClicked.RemoveAll(this);
	QuitButton->OnHovered.RemoveAll(this);
	QuitButton->OnUnhovered.RemoveAll(this);
}

