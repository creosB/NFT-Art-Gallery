// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArtInformation.h"
#include "Blueprint/UserWidget.h"
#include "WebPayment.generated.h"


UCLASS()
class CRYPTOTEST_API UWebPayment : public UUserWidget
{
	GENERATED_BODY()

public:
	FText SetUrl(const FText& URL);
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CollectionName;

private:
	UPROPERTY(meta = (BindWidget), EditAnywhere)
	UWebBrowser* WebWidget;
	UPROPERTY(meta = (BindWidget))
	UCircularThrobber* ImageLoading;
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UFUNCTION()
	void OnClickClose();
	UFUNCTION()
	void WebUrl(const FText& URL);

	FText TempUrl;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
