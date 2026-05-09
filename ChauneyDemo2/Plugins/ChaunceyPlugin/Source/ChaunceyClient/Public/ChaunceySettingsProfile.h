// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChaunceySettingsProfile.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CHAUNCEYCLIENT_API UChaunceySettingsProfile : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chauncey")
	FString DatarouterURL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chauncey")
	FString ApiURL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chauncey")
	FString AppURL;
};
