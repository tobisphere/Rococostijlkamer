// Copyright 2023, Ryan Shetley. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "WebBridgeSubsystem.h"
#include "Delegates/Delegate.h"
#include "Components/Widget.h"
#include "WebBridgeBrowserWidget.generated.h"

class UWebBridgeExtension;
enum class EWebBrowserConsoleLogSeverity;

/**
 * 
 */
UCLASS()
class WEBBRIDGE_API UWebBridgeBrowserWidget : public UWidget
{
	GENERATED_UCLASS_BODY()
	
	public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConsoleMessage, const FString&, Message, const FString&, Source, int32, Line);

	UFUNCTION(BlueprintCallable, Category="Web Scripting")
	void LoadScriptObject(TSubclassOf<UWebBridgeExtension> InScriptObject);

	UFUNCTION(BlueprintCallable, Category="Web Scripting")
	void UnloadScriptObject(UWebBridgeExtension* InScriptObject);
	
	/**
	 * Load the specified URLo
	 *
	 * @param NewURL New URL to load
	 */
	UFUNCTION(BlueprintCallable, Category="Web Browser")
	void LoadURL(FString NewURL);

	/**
	 * Load a string as data to create a web page
	 *
	 * @param Contents String to load
	 * @param DummyURL Dummy URL for the page
	 */
	UFUNCTION(BlueprintCallable, Category="Web Browser")
	void LoadString(FString Contents, FString DummyURL);

	/**
	* Executes a JavaScript string in the context of the web page
	*
	* @param ScriptText JavaScript string to execute
	*/
	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	void ExecuteJavascript(const FString& ScriptText);

	/**
	 * Get the current title of the web page
	 */
	UFUNCTION(BlueprintCallable, Category="Web Browser")
	FText GetTitleText() const;

	/**
	* Gets the currently loaded URL.
	*
	* @return The URL, or empty string if no document is loaded.
	*/
	UFUNCTION(BlueprintCallable, Category = "Web Browser")
	FString GetUrl() const;
	
	/** Called when the browser has console spew to print */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnConsoleMessage OnConsoleMessage;

	/** Called when the browser has console spew to print */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnLoadDelegate OnLoadCompleted;

	/** Called when the browser has console spew to print */
	UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")
	FOnLoadDelegate OnLoadStarted;

public:

	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
	
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	UPROPERTY()
	UWebBridgeBrowser* Browser;

protected:
	/** URL that the browser will initially navigate to. The URL should include the protocol, eg http:// */
	UPROPERTY(EditAnywhere, Category=Appearance)
	FString InitialURL;
	
	
	void HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity);
	virtual void HandleOnLoadStarted() const;
	virtual void HandleOnLoadCompleted() const;
};
