// Copyright 2023, Ryan Shetley. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "WebJSFunction.h"
#include "UObject/Object.h"
#include "WebBridgeExtension.generated.h"

class UWebBridgeBrowser;
class UWebBridgeBrowserWidget;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class WEBBRIDGE_API UWebBridgeExtension : public UObject
{
	GENERATED_BODY()

public:
	UWebBridgeExtension();
	// UObject Interface
	virtual UWorld* GetWorld() const override;
	// End UObject Interface

	UFUNCTION()
	void Call(const FString& FuncName, const FString& JsonString, FWebJSResponse JavascriptResponse);
	
	
	void SetWorld(UWorld* InWorld);
	void SetHost(UWebBridgeBrowser* InHost);
	

	/*
	 * Can be a relative filepath from the Web object's local path, or any standard web url.
	 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category=WebBridge)
	FString Url;

	UPROPERTY(BlueprintReadOnly, Category=WebBridge)
	bool bIsReady;
	
	UFUNCTION(BlueprintCallable, Category=WebBridge)
	void ExecuteJavascript(const FString& InCode);
	
	UFUNCTION(BlueprintCallable, Category=WebBridge)
	void SetPropertyEvent(const FString& PropertyName, const TArray<FString>& Arguments);

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadStarted();

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadCompleted();
	
	UPROPERTY(BlueprintReadOnly, Category=WebBridge)
	UWorld* World;

	FString GetWebObjectName();
protected:
	UPROPERTY()
	UWebBridgeBrowser* Host;
};
