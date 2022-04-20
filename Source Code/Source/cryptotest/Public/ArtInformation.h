// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Http.h"
#include "HttpTest.h"
#include "JsonData.h"
#include "Components/Overlay.h"

#include "ArtInformation.generated.h"

class URichTextBlock;
class UTextBlock;
class UButton;
class UWebBrowser;
class UImage;
class UCircularThrobber;
class UWebPayment;
class UWidgetAnimation;


UCLASS()
class CRYPTOTEST_API UArtInformation : public UUserWidget
{
	GENERATED_BODY()
public:
	// get info from httptest page
	int32 CollectionNumber = 1;
	FString Collection = "";
	TSubclassOf<UWebPayment> BrowserWidget;
	FText BrowserUrl;
	UWebPayment* ScreenWidget;
	FJsonData JsonData;
	void SetInformation();

private:
	// TextBlocks
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CollectionName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Username;
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* Information;
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* DiscordRichText;
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* TwitterRichText;
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* InstagramRichText;

	// Buttons
	UPROPERTY(meta = (BindWidget))
	UButton* OpenSeaButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BinanceButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	// Images
	UPROPERTY(meta = (BindWidget))
	UImage* NFTImage;
	UPROPERTY(meta = (BindWidget))
	UCircularThrobber* ImageLoading;
	
	FHttpModule* Http;

	AcryptotestCharacter* Player = nullptr;
	APlayerController* PlayerController = nullptr;

	// Click Widget functions
	UFUNCTION()
	void OnClickOpenSea();
	UFUNCTION()
	void OnClickClose();
	UFUNCTION()
	void OnClickBinance();
	
	UFUNCTION()
	void OnGetTexture2D(UTexture2DDynamic* _texture);

	// ANIMATION
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* FadeIn; // animation
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_0;

	// HTTP request functions
	void PostArea();
	void OnProccessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
