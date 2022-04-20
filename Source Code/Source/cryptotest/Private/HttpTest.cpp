// Fill out your copyright notice in the Description page of Project Settings.


#include "cryptotest/Public/HttpTest.h"

#include "cryptotest/Public/WebPayment.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Texture2DDynamic.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

// Sets default values
AHttpTest::AHttpTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	// base mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paint"));
	Mesh->SetupAttachment(RootComponent);
	// painting text
	CreatorText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Creator Name"));
	Line = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Line"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AHttpTest::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AHttpTest::OnOverlapEnd);
	Trigger->SetupAttachment(Root);

	Http = &FHttpModule::Get(); // get http module
}

// Called when the game starts or when spawned
void AHttpTest::BeginPlay()
{
	Super::BeginPlay();

	// reset all texture function
	/*	if (TempTexture && Instance && BaseInstance)
		{
			this->Instance->SetMaterialInstanceTextureParameterValue(BaseInstance,TEXT("Painting Texture"), TempTexture);
		}
	*/
	GetPlayerInformation();
	PostArea(); // http call
	ForceNetUpdate();
	FlushNetDormancy();
}

// Called every frame
void AHttpTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player && Player->IsPressed && Trigger->IsOverlappingActor(Player))
	{
		SendArtInfo();
	}
}

void AHttpTest::GetPlayerInformation()
{
	// GetPlayer Information
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	PlayerController = World->GetFirstPlayerController();

	if (PlayerController != nullptr)
	{
		Player = Cast<AcryptotestCharacter>(
			UGameplayStatics::GetPlayerCharacter(World, UGameplayStatics::GetPlayerControllerID(PlayerController)));
	}
}


// send http request
void AHttpTest::PostArea()
{
	// create request
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	// bind to object
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpTest::OnProccessRequestComplete);
	// Request Settings - GET -
	Request->SetURL(
		"https://testnets-api.opensea.io/api/v1/assets?order_direction=desc&offset=0&limit=50&collection=" + FString(
			CollectionName)
	);
	// request url
	Request->SetVerb("GET"); // request type
	Request->SetHeader("Content-Type", TEXT("application/json")); // set json format


	//	FJsonData assets = FJsonData(JsonString);
	//	FJsonObjectConverter::UStructToJsonObjectString(assets.assets[0].id,JsonString);
	//	Request->SetContentAsString(JsonString);
	Request->ProcessRequest(); // send request
}

// HTTP Response
void AHttpTest::OnProccessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{
	TSharedPtr<FJsonObject> JsonObject;
	// convert from json and set all
	if (Success)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());

		const FString JsonString = Response->GetContentAsString();

		/*
		// call all json
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> ArtArray = JsonObject->GetArrayField("assets");
			for (const TSharedPtr<FJsonValue> UserValue : ArtArray)
			{
				JsonData = FJsonData(JsonString);
			}
		}
	*/


		JsonData = FJsonData(JsonString);
		if (JsonData.assets.Num() > 0)
		{
			Download = NewObject<UAsyncTaskDownloadImage>();
			Download->OnFail.AddDynamic(this, &AHttpTest::OnFailedTextureDownload);
			Download->OnSuccess.AddDynamic(this, &AHttpTest::OnGetTexture2D);
			Download->Start(*JsonData.assets[CollectionNumber - 1].image_url);
			if (CreatorText)
			{
				CreatorText->SetText(
					FText::FromString(*JsonData.assets[CollectionNumber - 1].asset_contract.name));
			}
		}
	}
}

/*
  *** Trigger Area ***
*/
void AHttpTest::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Player != nullptr && OtherActor != nullptr)
	{
		if (OtherActor == Player)
		{
			// it's adding interaction widget to viewport
			ScreenWidget = CreateWidget<UUserWidget>(GetWorld(), InteractWidget);
			if (ScreenWidget && !this->ScreenWidget->IsInViewport())
			{
				this->ScreenWidget->AddToViewport();
			}
		}
	}
}


void AHttpTest::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex)
{
	// check and delete all widgets
	if (Player != nullptr && OtherActor != nullptr && OtherActor != this)
	{
		if (IsValid(ScreenWidget))
		{
			ScreenWidget->RemoveFromParent();
		}
		if (IsValid(ArtWidget))
		{
			ArtWidget->RemoveFromParent();
		/*	if (IsValid(ArtWidget->ScreenWidget))
			{
				ArtWidget->ScreenWidget->RemoveFromParent();
			}*/
		}
		Player->IsPressed = false;
	}
}

// Send info to art information widget
void AHttpTest::SendArtInfo()
{
	if (ArtWidget && !this->ArtWidget->IsInViewport())
	{
		// set art information with properties and add to user screen
		ArtWidget->JsonData = JsonData;
		ArtWidget->Collection = CollectionName;
		ArtWidget->CollectionNumber = CollectionNumber;
		ArtWidget->BrowserUrl = BrowserUrl;
		ArtWidget->BrowserWidget = WebPayment;
		this->ArtWidget->AddToViewport();
	}
}

// if successful downloaded it will change painting texture
void AHttpTest::OnGetTexture2D(UTexture2DDynamic* _texture)
{
	TryDownload += 10; // set value for successful download
	if (TargetMaterial)
	{
		Mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(MaterialIndex, TargetMaterial)->SetTextureParameterValue(
			TEXT("Painting Texture"), _texture);
	}
}

// fail func.
void AHttpTest::OnFailedTextureDownload(UTexture2DDynamic* _texture)
{
	TryDownload += 1;
	if (TryDownload <= 2)
	{
		Download->Start(*JsonData.assets[CollectionNumber - 1].image_url);
	}
	UE_LOG(LogTemp, Warning, TEXT("I can't download this image"));
}
