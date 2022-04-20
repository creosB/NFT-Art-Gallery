// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerList.h"
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UServerList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// if you select or hover one server it will change the color
	if (Selected)
	{
		ServerName->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0.29167, 0.5)));
		PingText->SetColorAndOpacity(ServerName->ColorAndOpacity);
	}
	else
	{
		if (ServerName->IsHovered()) // || PlayerNumber->IsHovered())
		{
			ServerName->SetColorAndOpacity(FLinearColor::Yellow);
			PingText->SetColorAndOpacity(ServerName->ColorAndOpacity);
		}
		else
		{
			ServerName->SetColorAndOpacity(FLinearColor::White);
			PingText->SetColorAndOpacity(ServerName->ColorAndOpacity);
		}
	}
}


void UServerList::Setup(UMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	SelectButton->OnClicked.AddDynamic(this, &UServerList::OnClicked);
}

// return pressed button index
void UServerList::OnClicked()
{
	Parent->SelectIndex(Index);
}