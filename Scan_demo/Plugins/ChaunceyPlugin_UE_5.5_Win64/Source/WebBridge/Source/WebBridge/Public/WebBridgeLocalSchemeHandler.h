// Copyright 2023, Ryan Shetley. All Rights Reserved.

#pragma once
#include "IWebBrowserSchemeHandler.h"

class WebBridgeLocalSchemeHandler : public IWebBrowserSchemeHandler
{
public:
	explicit WebBridgeLocalSchemeHandler(const FString& InBasePath, const FString& InRequestUrl);
	
	virtual void GetResponseHeaders(IHeaders& OutHeaders) override;
	virtual bool ReadResponse(uint8* OutBytes, int32 BytesToRead, int32& BytesRead,
		const FSimpleDelegate& OnMoreDataReady) override;
	virtual void Cancel() override;

	virtual bool
	ProcessRequest(const FString& Verb, const FString& Url, const FSimpleDelegate& OnHeadersReady) override;

private:
	// Apply a "root" directory, that requests can't "break" out of for security purposes
	FString BasePath;
	FString RequestUrl;
	IFileHandle* FileHandle;
	int64 RemainingBytes = 0;
};
