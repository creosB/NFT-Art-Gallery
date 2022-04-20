// Fill out your copyright notice in the Description page of Project Settings.


#include "cryptotest/Public/WebPayment.h"
#include "WebBrowser.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"

void UWebPayment::NativeConstruct()
{
	Super::NativeConstruct();
	WebWidget->OnUrlChanged.AddDynamic(this, &UWebPayment::WebUrl);
	CloseButton->OnClicked.AddDynamic(this, &UWebPayment::OnClickClose);
}

FText UWebPayment::SetUrl(const FText& URL)
{
	return TempUrl = URL;
}

void UWebPayment::WebUrl(const FText& URL)
{
	if (WebWidget && ImageLoading)
	{
		ImageLoading->SetVisibility(ESlateVisibility::Collapsed);
		WebWidget->SetVisibility(ESlateVisibility::Visible);
		WebWidget->LoadURL(TempUrl.ToString());
	}
	WebWidget->OnUrlChanged.Clear();
}

void UWebPayment::OnClickClose()
{
	WebWidget->OnUrlChanged.Clear();
	this->SetVisibility(ESlateVisibility::Collapsed);
	this->RemoveFromParent();
}

void UWebPayment::NativeDestruct()
{
	Super::NativeDestruct();

	WebWidget->OnUrlChanged.RemoveAll(this);
	CloseButton->OnClicked.RemoveAll(this);
}

