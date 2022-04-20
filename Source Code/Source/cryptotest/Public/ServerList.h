// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerList.generated.h"

class UTextBlock;

UCLASS()
class CRYPTOTEST_API UServerList : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName; // server name text block widget
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PingText;
	/*UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNumber; // player number text block widget */

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false; // selection logic
	void Setup(class UMainMenu* Parent, uint32 Index);
private:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UFUNCTION()
	void OnClicked();

	UPROPERTY()
	UMainMenu* Parent;
	uint32 Index;
};
