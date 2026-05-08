// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaunceySettingsProfile.h"
#include "Engine/DeveloperSettings.h"
#include "ChaunceySettings.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FChaunceySettingsChangedDelegate, UChaunceySettingsProfile*);
UCLASS(Config=Chauncey, defaultconfig, meta = (DisplayName="Chauncey Settings"))
class CHAUNCEYCLIENT_API UChaunceySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	FChaunceySettingsChangedDelegate& OnSettingsChanged()
	{
		return SettingsChanged;
	}
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Chauncey")
	TSoftObjectPtr<UChaunceySettingsProfile> SettingsProfile;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Chauncey")
	FString ConnectionTag = "unreal";
	
private:
	FChaunceySettingsChangedDelegate SettingsChanged;
	
};
