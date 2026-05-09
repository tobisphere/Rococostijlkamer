#pragma once
#include "ChaunceyTypes.generated.h"

USTRUCT()
struct FChaunceyTokenData
{
	GENERATED_BODY()

	UPROPERTY()
	FString UserId;

	UPROPERTY()
	FString AccessToken;

	UPROPERTY()
	FString RefreshToken;

	bool IsValid() const
	{
		return !AccessToken.IsEmpty();
	}
};

USTRUCT(BlueprintType)
struct FChaunceyChannel
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Channel_Group_Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString System_Label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Type;
	
};

USTRUCT(BlueprintType)
struct FChaunceyChannelGroup
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Snapshot_Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	TArray<FChaunceyChannel> Channels;
};

USTRUCT(BlueprintType)
struct FChaunceyDevAPIKey
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Workspace_Id;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Label;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Public_Key;
};

// partial
USTRUCT(BlueprintType)
struct FChaunceyWorkspace
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FChaunceyDevAPIKey Dev_ApiKey;

	bool IsValid() const
	{
		return !(Id.IsEmpty() || Name.IsEmpty());
	}
};


// partial
USTRUCT(BlueprintType)
struct FChaunceyProject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Title;

	bool IsValid() const
	{
		return !(Id.IsEmpty() || Title.IsEmpty());
	}
};

// partial
USTRUCT(BlueprintType)
struct FChaunceySnapshot
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	bool Enabled = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Chauncey)
	TArray<FChaunceyChannelGroup> Channel_Groups;
};