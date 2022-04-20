#pragma once

#include "Engine/DataTable.h"

#include "SettingsDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FSettingsDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FSettingsDataStruct()
		: ScreenResolution("1920x1080")
		,ViewDistance("Far")
		,AntiAliasing("Epic")
		,ShadowQuality("Ultra")
		,TextureQuality("Ultra")
		,VsyncQuality("on")
		,MasterVolume(1.0f)
		,MusicVolume(1.0f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString ScreenResolution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString ViewDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString AntiAliasing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString ShadowQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString TextureQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString VsyncQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	float MasterVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	float MusicVolume;
};
