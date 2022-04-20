// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "PauseMenu.generated.h"

class UButton;

UCLASS()
class CRYPTOTEST_API UPauseMenu : public UMenuWidget
{
	GENERATED_BODY()

	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	void OnClosed();
	
	// On Click
	UFUNCTION()
	void MainMenu();
	UFUNCTION()
	void Cancel();
	UFUNCTION()
	void Quit();

	// ON HOVERED
	UFUNCTION()
	void OnHoveredMainMenu();
	UFUNCTION()
	void OnHoveredCancel();
	UFUNCTION()
	void OnHoveredQuit();

	// ON UNHOVERED
	UFUNCTION()
	void OnUnHoveredMainMenu();
	UFUNCTION()
	void OnUnHoveredCancel();
	UFUNCTION()
	void OnUnHoveredQuit();

	// ANIMATONS
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* MainMenuAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* CancelAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* QuitAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* Pause;

	FTimerHandle AnimTimer;

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

};
