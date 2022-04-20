// Fill out your copyright notice in the Description page of Project Settings.


#include "cryptotest/Public/ArtInformation.h"
#include "cryptotest/Public/WebPayment.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CircularThrobber.h"
#include "Kismet/GameplayStatics.h"
#include "RunTime/UMG/Public/Blueprint/AsyncTaskDownloadImage.h"

void UArtInformation::NativeConstruct()
{
	Super::NativeConstruct();

	// get http module
	Http = &FHttpModule::Get();

	// button bindings
	this->OpenSeaButton->OnClicked.AddDynamic(this, &UArtInformation::UArtInformation::OnClickOpenSea);
	this->BinanceButton->OnClicked.AddDynamic(this, &UArtInformation::OnClickBinance);
	this->CloseButton->OnClicked.AddDynamic(this, &UArtInformation::OnClickClose);

	// get player controller
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	PlayerController = World->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		Player = Cast<AcryptotestCharacter>(
			UGameplayStatics::GetPlayerCharacter(World, UGameplayStatics::GetPlayerControllerID(PlayerController)));
	};
	if (Player && PlayerController)
	{
		Player->DisableInput(PlayerController);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, this, EMouseLockMode::DoNotLock, true);
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}

	// check data
	if (JsonData.assets.Num() <= 0)
	{
		PostArea();
	}
	else
	{
		SetInformation();
	}


	// call and play animation
	if (FadeIn)
	{
		PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.5f, true);
		Overlay_0->SetVisibility(ESlateVisibility::Visible);
	}
}

// set all widget information
void UArtInformation::SetInformation()
{
	// set all information with api answer
	if (Information)
	{
		Information->SetText(FText::FromString(*JsonData.assets[CollectionNumber - 1].asset_contract.description));
	}
	if (CollectionName)
	{
		CollectionName->SetText(FText::FromString(*JsonData.assets[CollectionNumber - 1].asset_contract.name));
	}
	if (Username)
	{
		Username->SetText(FText::FromString(*JsonData.assets[CollectionNumber - 1].creator.user.username));
	}

	// discord text check
	if (DiscordRichText)
	{
		// add text with decorator
		if (FString(*JsonData.assets[CollectionNumber - 1].collection.discord_url) != "null")
		{
			DiscordRichText->SetText(FText::FromString(
				FString("<img id=\"Discord\"/>	") + *JsonData.assets[CollectionNumber - 1].collection.discord_url));
		}
		else
		{
			// when it turned null it will hide
			DiscordRichText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	// instagram text check
	if (InstagramRichText)
	{
		if (FString(*JsonData.assets[CollectionNumber - 1].collection.instagram_username) != "null")
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"),
			       *JsonData.assets[CollectionNumber - 1].collection.instagram_username);
			// add text with decorator
			InstagramRichText->SetText(FText::FromString(
				FString("<img id=\"Instagram\"/>	") + *JsonData.assets[CollectionNumber - 1].collection.instagram_username));
		}
		else
		{
			// when it turned null it will hide
			InstagramRichText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	// twitter text check
	if (TwitterRichText)
	{
		if (FString(*JsonData.assets[CollectionNumber - 1].collection.twitter_username) != "null")
		{
			// add text with decorator
			TwitterRichText->SetText(FText::FromString(
				FString("<img id=\"Twitter\"/>	") + *JsonData.assets[CollectionNumber - 1].collection.twitter_username));
		}
		else
		{
			// when it turned null it will hide
			TwitterRichText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	// IMAGE
	if (NFTImage)
	{
		UAsyncTaskDownloadImage* Download = NewObject<UAsyncTaskDownloadImage>();
		Download->OnSuccess.AddDynamic(this, &UArtInformation::OnGetTexture2D);
		Download->Start(*JsonData.assets[CollectionNumber - 1].image_url);
	}
}

/*
 *** API AREA ***
*/
// sent api request
void UArtInformation::PostArea()
{
	// create request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	// bind to object
	Request->OnProcessRequestComplete().BindUObject(this, &UArtInformation::OnProccessRequestComplete);
	// Request Settings - GET -
	Request->SetURL(
		"https://testnets-api.opensea.io/api/v1/assets?order_direction=desc&offset=0&limit=50&collection=" +
		FString(Collection));
	// request url
	Request->SetVerb("GET"); // request type
	Request->SetHeader("Content-Type", TEXT("application/json")); // set json format

	Request->ProcessRequest(); // send request
}

// get response
void UArtInformation::OnProccessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	TSharedPtr<FJsonObject> JsonObject;

	// convert from json and set all information
	if (Success)
	{
		const FString JsonString = Response->GetContentAsString();

		JsonData = FJsonData(JsonString); // convert data
		SetInformation(); // send data
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Request Failed!!!"));
	}
}

// download and set texture
void UArtInformation::OnGetTexture2D(UTexture2DDynamic* _texture)
{
	if (NFTImage && ImageLoading)
	{
		ImageLoading->SetVisibility(ESlateVisibility::Collapsed);
		NFTImage->SetVisibility(ESlateVisibility::Visible);
		NFTImage->SetBrushFromTextureDynamic(_texture, false);
	}
}

/*
	***Button Function Area*** 	
*/
// OpenSea button function
void UArtInformation::OnClickOpenSea()
{
	if (*JsonData.assets[CollectionNumber - 1].permalink != nullptr)
	{
		FPlatformProcess::LaunchURL(*JsonData.assets[CollectionNumber - 1].permalink, NULL, NULL);
	}
}

// Binance button function
void UArtInformation::OnClickBinance()
{
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAA"));
	// create and add to screen.
	if (BrowserWidget)
	{
		ScreenWidget = CreateWidget<UWebPayment>(GetWorld(), BrowserWidget);
		if (ScreenWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAA"));
			ScreenWidget->CollectionName->SetText(
					FText::FromString(*JsonData.assets[CollectionNumber - 1].asset_contract.name));
			ScreenWidget->SetUrl(BrowserUrl);
			ScreenWidget->AddToViewport();
		}
	}
}

void UArtInformation::OnClickClose()
{
	this->RemoveFromParent();

	if (Player && PlayerController)
	{
		FInputModeGameOnly InputModeData; // call the struct
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = false;
		Player->IsPressed = false;
		Player->EnableInput(PlayerController);
	}

	if (IsValid(ScreenWidget))
	{
		ScreenWidget->SetVisibility(ESlateVisibility::Collapsed);
		ScreenWidget->RemoveFromParent();
	}
}

void UArtInformation::NativeDestruct()
{
	Super::NativeDestruct();

	OpenSeaButton->OnClicked.RemoveAll(this);
	BinanceButton->OnClicked.RemoveAll(this);
	CloseButton->OnClicked.RemoveAll(this);
}


