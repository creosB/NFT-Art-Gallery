// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "cryptotestCharacter.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "JsonData.h"
#include "Materials/MaterialInstanceConstant.h"
#include "HttpTest.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UArtInformation;
class UTextRenderComponent;

UCLASS()
class CRYPTOTEST_API AHttpTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHttpTest();
	
	// Sharable Informations
	UPROPERTY(EditAnywhere, Category= "Art Information")
	int32 CollectionNumber = 1;
	UPROPERTY(EditAnywhere, Category= "Art Information")
	FString CollectionName = "";
	UPROPERTY(EditAnywhere, Category= "Art Information")
	FText BrowserUrl = FText::FromString("");

private:
	// Basic Config
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UBoxComponent* Trigger;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	// Cast
	AcryptotestCharacter* Player;
	APlayerController* PlayerController = nullptr;
	UPROPERTY(EditAnywhere)
	UArtInformation* ArtWidget;

	// Material Configurations
	UMaterialEditingLibrary* Instance;
	UPROPERTY(EditAnywhere, Category= "Art Information")
	UMaterial* TargetMaterial;
	UPROPERTY(EditAnywhere, Category= "Art Information")
	uint8 MaterialIndex = 0;

	// Text Actor
	UPROPERTY(EditAnywhere, Category= "Art Information")
	UTextRenderComponent* CreatorText; // creator name
	UPROPERTY(EditAnywhere, Category= "Art Information")
	UTextRenderComponent* Line;

	/*
	// if you want to reset all paintings you need to active this texture and function
	UPROPERTY(EditAnywhere);
	UTexture* TempTexture;
	*/

	// WebPayment
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WebPayment;
	
	// Interact Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InteractWidget;
	UUserWidget* ScreenWidget;

	// Http-json variable
	FJsonData JsonData;
	FHttpModule* Http;

	// Download
	class UAsyncTaskDownloadImage* Download;
	int8 TryDownload = 0;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SendArtInfo(); // art information widget
	void GetPlayerInformation();

	// Texture Download
	UFUNCTION()
	void OnGetTexture2D(UTexture2DDynamic* _texture);

	UFUNCTION()
	void OnFailedTextureDownload(UTexture2DDynamic* _texture);

	// HTTP request functions
	void PostArea();
	void OnProccessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
