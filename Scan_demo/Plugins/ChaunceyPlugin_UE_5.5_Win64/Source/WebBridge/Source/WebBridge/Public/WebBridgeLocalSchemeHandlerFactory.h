// Copyright 2023, Ryan Shetley. All Rights Reserved.
#pragma once
#include "IWebBrowserSchemeHandler.h"

class WebBridgeLocalSchemeHandlerFactory : public IWebBrowserSchemeHandlerFactory
{
public:
	WebBridgeLocalSchemeHandlerFactory(const FString& InBasePath);
	
	virtual TUniquePtr<IWebBrowserSchemeHandler> Create(FString Verb, FString Url) override;
private:
	FString BasePath;
};
