#pragma once

#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "CoreMinimal.h"
#include "JsonData.generated.h"

USTRUCT()
struct FJsonDataAssetTrait
{
	
	GENERATED_BODY()

	UPROPERTY()
	FString trait_type;

	UPROPERTY()
	FString value;

	UPROPERTY()
	int32 trait_count;

	FJsonDataAssetTrait()
	{
	};

	FJsonDataAssetTrait(FString _trait_type, FString _value, int32 _trait_count)
	{
		trait_type = _trait_type;
		value = _value;
		trait_count = _trait_count;
	}
};

USTRUCT()
struct FJsonDataAssetsCreatorUser
{
	GENERATED_BODY()

	UPROPERTY()
	FString username;

	FJsonDataAssetsCreatorUser()
	{
	};

	FJsonDataAssetsCreatorUser(FString _username)
	{
		username = _username;
	}
};

USTRUCT()
struct FJsonDataAssetCreator
{
	GENERATED_BODY()

	UPROPERTY()
	FJsonDataAssetsCreatorUser user;

	UPROPERTY()
	FString profile_img_url;

	UPROPERTY()
	FString address;

	UPROPERTY()
	FString config;

	FJsonDataAssetCreator()
	{
	};

	FJsonDataAssetCreator(FJsonDataAssetsCreatorUser _user, FString _profile_img_url, FString _address, FString _config)
	{
		user = _user;
		profile_img_url = _profile_img_url;
		address = _address;
		config = _config;
	}
};

USTRUCT()
struct FJsonDataAssetsOwnerUser
{
	GENERATED_BODY()

	UPROPERTY()
	FString username;

	FJsonDataAssetsOwnerUser()
	{
	};

	FJsonDataAssetsOwnerUser(FString _username)
	{
		username = _username;
	}
};

USTRUCT()
struct FJsonDataAssetOwner
{
	GENERATED_BODY()

	UPROPERTY()
	FJsonDataAssetsOwnerUser user;

	UPROPERTY()
	FString profile_img_url;

	UPROPERTY()
	FString address;

	UPROPERTY()
	FString config;

	FJsonDataAssetOwner()
	{
	};

	FJsonDataAssetOwner(FJsonDataAssetsOwnerUser _user, FString _profile_img_url, FString _address, FString _config)
	{
		user = _user;
		profile_img_url = _profile_img_url;
		address = _address;
		config = _config;
	}
};

USTRUCT()
struct FJsonDataAssetsCollectionDisplay_datum
{
	GENERATED_BODY()

	UPROPERTY()
	FString card_display_style;

	FJsonDataAssetsCollectionDisplay_datum()
	{
	};

	FJsonDataAssetsCollectionDisplay_datum(FString _card_display_style)
	{
		card_display_style = _card_display_style;
	}
};

USTRUCT()
struct FJsonDataAssetCollection
{
	GENERATED_BODY()

	UPROPERTY()
	FString banner_image_url;

	UPROPERTY()
	FString created_date;

	UPROPERTY()
	bool default_to_fiat;

	UPROPERTY()
	FString description;

	UPROPERTY()
	FString dev_buyer_fee_basis_points;

	UPROPERTY()
	FString dev_seller_fee_basis_points;

	UPROPERTY()
	FJsonDataAssetsCollectionDisplay_datum display_data;

	UPROPERTY()
	FString external_url;

	UPROPERTY()
	bool featured;

	UPROPERTY()
	bool hidden;

	UPROPERTY()
	FString safelist_request_status;

	UPROPERTY()
	FString image_url;

	UPROPERTY()
	bool is_subject_to_whitelist;

	UPROPERTY()
	FString large_image_url;

	UPROPERTY()
	FString medium_username;
	
	UPROPERTY()
	FString name;
	
	UPROPERTY()
	bool only_proxied_transfers;

	UPROPERTY()
	FString opensea_buyer_fee_basis_points;

	UPROPERTY()
	FString opensea_seller_fee_basis_points;

	UPROPERTY()
	FString discord_url;

	UPROPERTY()
	FString payout_address;

	UPROPERTY()
	bool require_email;

	UPROPERTY()
	FString slug;

	UPROPERTY()
	FString telegram_url;

	UPROPERTY()
	FString twitter_username;

	UPROPERTY()
	FString instagram_username;

	FJsonDataAssetCollection()
	{
	};

	FJsonDataAssetCollection(FString _banner_image_url, FString _created_date, bool _default_to_fiat,
	                         FString _description, FString _dev_buyer_fee_basis_points,
	                         FString _dev_seller_fee_basis_points, FString _discord_url,
	                         FJsonDataAssetsCollectionDisplay_datum _display_data,
	                         FString _external_url, bool _featured, bool _hidden, FString _safelist_request_status,
	                         FString _image_url, bool _is_subject_to_whitelist, FString _name,
	                         bool _only_proxied_transfers, FString _opensea_buyer_fee_basis_points,
	                         FString _opensea_seller_fee_basis_points, FString _payout_address, bool _require_email,
	                         FString _slug, FString _telegram_url, FString _twitter_username,
	                         FString _instagram_username
	)
	{
		banner_image_url = _banner_image_url;
		created_date = _created_date;
		default_to_fiat = _default_to_fiat;
		description = _description;
		dev_buyer_fee_basis_points = _dev_buyer_fee_basis_points;
		dev_seller_fee_basis_points = _dev_seller_fee_basis_points;
		discord_url = _discord_url;
		display_data = _display_data;
		external_url = _external_url;
		featured = _featured;
		hidden = _hidden;
		safelist_request_status = _safelist_request_status;
		image_url = _image_url;
		is_subject_to_whitelist = _is_subject_to_whitelist;
		name = _name;
		only_proxied_transfers = _only_proxied_transfers;
		opensea_buyer_fee_basis_points = _opensea_buyer_fee_basis_points;
		opensea_seller_fee_basis_points = _opensea_seller_fee_basis_points;
		payout_address = _payout_address;
		require_email = _require_email;
		slug = _slug;
		telegram_url = _telegram_url;
		instagram_username = _instagram_username;
		twitter_username = _twitter_username;
	}
};

USTRUCT()
struct FJsonDataAssetAsset_contract
{
	GENERATED_BODY()

	UPROPERTY()
	FString address;

	UPROPERTY()
	FString asset_contract_type;

	UPROPERTY()
	FString created_date;

	UPROPERTY()
	FString name;

	UPROPERTY()
	FString nft_version;

	UPROPERTY()
	int32 owner;

	UPROPERTY()
	FString schema_name;

	UPROPERTY()
	FString symbol;

	UPROPERTY()
	FString total_supply;

	UPROPERTY()
	FString description;

	UPROPERTY()
	FString external_link;

	UPROPERTY()
	FString image_url;

	UPROPERTY()
	bool default_to_fiat;

	UPROPERTY()
	int32 dev_buyer_fee_basis_points;

	UPROPERTY()
	int32 dev_seller_fee_basis_points;

	UPROPERTY()
	bool only_proxied_transfers;

	UPROPERTY()
	int32 opensea_buyer_fee_basis_points;

	UPROPERTY()
	int32 opensea_seller_fee_basis_points;

	UPROPERTY()
	int32 buyer_fee_basis_points;

	UPROPERTY()
	int32 seller_fee_basis_points;

	UPROPERTY()
	FString payout_address;

	FJsonDataAssetAsset_contract()
	{
	};

	FJsonDataAssetAsset_contract(FString _address, FString _asset_contract_type, FString _created_date, FString _name,
	                             FString _nft_version, int32 _owner, FString _schema_name, FString _symbol,
	                             FString _total_supply, FString _description, FString _external_link,
	                             FString _image_url, bool _default_to_fiat, int32 _dev_buyer_fee_basis_points,
	                             int32 _dev_seller_fee_basis_points, bool _only_proxied_transfers,
	                             int32 _opensea_buyer_fee_basis_points, int32 _opensea_seller_fee_basis_points,
	                             int32 _buyer_fee_basis_points, int32 _seller_fee_basis_points, FString _payout_address)
	{
		address = _address;
		asset_contract_type = _asset_contract_type;
		created_date = _created_date;
		name = _name;
		nft_version = _nft_version;
		owner = _owner;
		schema_name = _schema_name;
		symbol = _symbol;
		total_supply = _total_supply;
		description = _description;
		external_link = _external_link;
		image_url = _image_url;
		default_to_fiat = _default_to_fiat;
		dev_buyer_fee_basis_points = _dev_buyer_fee_basis_points;
		dev_seller_fee_basis_points = _dev_seller_fee_basis_points;
		only_proxied_transfers = _only_proxied_transfers;
		opensea_buyer_fee_basis_points = _opensea_buyer_fee_basis_points;
		opensea_seller_fee_basis_points = _opensea_seller_fee_basis_points;
		buyer_fee_basis_points = _buyer_fee_basis_points;
		seller_fee_basis_points = _seller_fee_basis_points;
		payout_address = _payout_address;
	}
};

USTRUCT()
struct FJsonDataAsset
{
	GENERATED_BODY()

	UPROPERTY()
	int32 id;

	UPROPERTY()
	int32 num_sales;
	
	UPROPERTY()
	FString image_url;

	UPROPERTY()
	FString image_preview_url;

	UPROPERTY()
	FString image_thumbnail_url;

	UPROPERTY()
	FString image_original_url;

	
	UPROPERTY()
	FString name;
	
	UPROPERTY()
	FJsonDataAssetAsset_contract asset_contract;

	UPROPERTY()
	FString permalink;

	UPROPERTY()
	FJsonDataAssetCollection collection;

	UPROPERTY()
	int32 decimals;

	UPROPERTY()
	FString token_metadata;

	UPROPERTY()
	FJsonDataAssetOwner owner;

	UPROPERTY()
	FJsonDataAssetCreator creator;

	UPROPERTY()
	TArray<FJsonDataAssetTrait> traits;

	UPROPERTY()
	bool is_presale;

	UPROPERTY()
	FString token_id;

	FJsonDataAsset()
	{
	};

	FJsonDataAsset(int32 _id, int32 _num_sales, FString _image_url, FString _image_preview_url,
	               FString _image_thumbnail_url, FString _image_original_url,
	               FJsonDataAssetAsset_contract _asset_contract, FString _permalink,
	               FJsonDataAssetCollection _collection, int32 _decimals, FString _token_metadata,
	               FJsonDataAssetOwner _owner, FJsonDataAssetCreator _creator, TArray<FJsonDataAssetTrait> _traits,
	               bool _is_presale, FString _token_id)
	{
		id = _id;
		num_sales = _num_sales;
		image_url = _image_url;
		image_preview_url = _image_preview_url;
		image_thumbnail_url = _image_thumbnail_url;
		image_original_url = _image_original_url;
		asset_contract = _asset_contract;
		permalink = _permalink;
		collection = _collection;
		decimals = _decimals;
		token_metadata = _token_metadata;
		owner = _owner;
		creator = _creator;
		traits = _traits;
		is_presale = _is_presale;
		token_id = _token_id;
	}
};

USTRUCT()
struct FJsonData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FJsonDataAsset> assets;

	FJsonData()
	{
	};

	FJsonData(TArray<FJsonDataAsset> _assets)
	{
		assets = _assets;
	}

	/* Don't Forget to setup your project
	Add #include "Runtime/JsonUtilities/Public/JsonObjectConverter.h" in 
	file with this structs.
	Also you need add "Json", "JsonUtilities" in Build.cs */

	FJsonData(FString _json_)
	{
		FJsonData _tmpJsonData;

		FJsonObjectConverter::JsonObjectStringToUStruct<FJsonData>(
			_json_,
			&_tmpJsonData,
			0, 0);

		assets = _tmpJsonData.assets;
	}
};

