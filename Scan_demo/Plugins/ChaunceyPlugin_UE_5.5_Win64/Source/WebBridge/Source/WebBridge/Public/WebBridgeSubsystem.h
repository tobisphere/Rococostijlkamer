// Copyright 2023, Ryan Shetley. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#if WITH_EDITOR
#include "Editor.h"
#endif
#include "SWebBrowserView.h"
#include "WebBridgeSubsystem.generated.h"

class UWebBridgeBrowser;

UCLASS()
class WEBBRIDGE_API UWebBridgeSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	/** Static convenience method to return this subsystem */
	static UWebBridgeSubsystem* Get();

	// Used just to be able to recall this later if needed
	FString RootCachePath;
	
	UWebBridgeBrowser* CreateBrowserWindow(
		const FString& ContextName = FString(TEXT("UWebBridgeBrowserContext")),
		const FString& CachePath = "",
		const FString& LocalPublicDir = "",
		const FSimpleDelegate& InLoadStartedDelegate = nullptr,
		const FSimpleDelegate& InLoadCompletedDelegate  = nullptr,
		const FOnConsoleMessageDelegate& InConsoleMessageDelegate = nullptr);
};