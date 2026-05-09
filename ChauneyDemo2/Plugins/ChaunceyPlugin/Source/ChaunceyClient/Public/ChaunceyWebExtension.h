#pragma once
#include "WebBridgeExtension.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "ChaunceyWebExtension.generated.h"

struct FWebBrowserCookie;

DECLARE_DELEGATE_TwoParams(FChaunceyCallbackDelegate, TSharedPtr<FJsonValue> JsonConfig, TSharedPtr<FJsonValue> JsonObject)

UCLASS()
class UChaunceyWebExtension : public UWebBridgeExtension
{
	#define CREATE_JS_DELEGATE(RegexString, DelegateName) \
FChaunceyCallbackDelegate DelegateName##Delegate; \
DelegateName##Delegate.BindUObject(this, &UChaunceyWebExtension::DelegateName); \
UrlResponseCallbacks.Add(TEXT(RegexString), DelegateName##Delegate);
	
	GENERATED_BODY()
public:
	UChaunceyWebExtension();
private:
	
	/*
	 * UWebBridgeExtension Interface
	 */
	virtual void OnLoadCompleted_Implementation() override;
	virtual void OnLoadStarted_Implementation() override;
	/*
	 * End UWebBridgeExtension Interface
	 */

	/*
	 * Patches the window.fetch functionality in the Chauncey web app world so that we can directly react to user interactions.
	 */
	void PatchJavascriptFetch();

	/*
	 * Called to store a browser cookie.
	 */
	void StoreAuthCookie(const FWebBrowserCookie& InAuthCookie);
	
	bool bLoggedIn;

	/*
	 * Events and properties to manage the events from Javascript
	 */

	TMap<FString, FChaunceyCallbackDelegate> UrlResponseCallbacks;
	
	// Called when a REST response is available via the webapp
	UFUNCTION()
	void OnJavascriptFetchResponse(const FString& InUrl, const FString& InConfig, const FString& InJsonResponse);
	
	/*
	 * Functions that will be called directly from the Chauncey web app JS
	 */
	void OnLogin(TSharedPtr<FJsonValue> JsonConfig, TSharedPtr<FJsonValue> JsonValue); //const FString& InAccessToken, const FString& InRefreshToken, const FString& InUserId);
	void OnLogout(TSharedPtr<FJsonValue> JsonConfig, TSharedPtr<FJsonValue> JsonValue);
	void OnFolders(TSharedPtr<FJsonValue> JsonConfig, TSharedPtr<FJsonValue> JsonValue);
	void OnControllers(TSharedPtr<FJsonValue> JsonConfig, TSharedPtr<FJsonValue> JsonValue);
};
