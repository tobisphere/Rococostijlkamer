// Copyright 2023, Ryan Shetley. All Rights Reserved.
#pragma once
#include "SWebBrowserView.h"
#include "WebBridgeBrowser.generated.h"

class UWebBridgeExtension;
class IWebBrowserWindow;
class SWebBrowser;

UCLASS(NotBlueprintable)
class WEBBRIDGE_API UWebBridgeBrowser: public UObject
{
public:
	GENERATED_BODY()

	UWebBridgeBrowser() {};
	
	bool Init(const FBrowserContextSettings& InContextSettings,
		const FSimpleDelegate& InLoadStartedDelegate,
		const FSimpleDelegate& InLoadCompletedDelegate,
		const FOnConsoleMessageDelegate& InConsoleMessageDelegate);
	
	void LoadURL(const FString& InURL);
	void LoadString(const FString& Contents, const FString& DummyURL);
	void ExecuteJavascript(const FString& InScriptText);

	FText GetTitleText() const;
	FString GetUrl() const;

	UWebBridgeExtension* LoadExtension(const TSubclassOf<UWebBridgeExtension> InExtensionClass);
	void UnloadScriptObject(UWebBridgeExtension* InScriptObject);

	TSharedPtr<IWebBrowserCookieManager> GetCookieManager();
	
	UPROPERTY()
	TArray<UWebBridgeExtension*> WebExtensions;
	
	FCreateBrowserWindowSettings WindowSettings;
	TSharedPtr<SWebBrowser> WebBrowser;
	TSharedPtr<IWebBrowserWindow> WebBrowserWindow;
};
