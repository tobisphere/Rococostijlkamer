// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaunceyTypes.h"
#include "ChaunceyWebExtension.h"
#include "Subsystems/EngineSubsystem.h"
#include "ChaunceySubsystem.generated.h"

class UChaunceyDataContext;
class UChaunceyDataRouter;
class UChaunceyRestAPI;

DECLARE_EVENT_TwoParams(UChaunceySubsystem, FChaunceySubsystemPublishEvent, const FGuid&, TSharedPtr<FJsonObject>);

/**
 * 
 */
UCLASS()
class CHAUNCEYCLIENT_API UChaunceySubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	/** Static convenience method to return this subsystem */
	static UChaunceySubsystem* Get();
	UWebBridgeBrowser* InitBrowser();


	UFUNCTION()
	UChaunceyRestAPI* GetRestAPI() const
	{
		return RestAPI;
	}

	UFUNCTION()
	UChaunceyDataContext* GetDataContext() const
	{
		return DataContext;
	}
	
	UFUNCTION()
	void UpdateTokens(const FChaunceyTokenData& InTokenData);

	UFUNCTION()
	void LoadTokenDataFromDisk();
	
	const FChaunceyTokenData& GetTokenData() { return TokenData; }
	


	void SyncWorkspaceData();
	
	TMultiMap<TPair<FName, FName>, FGuid> PublishBindings;

	FChaunceySubsystemPublishEvent OnPublish;
private:
	
	FString CachePath;
	FString TokenPath;
	
	FChaunceyTokenData TokenData;

	UPROPERTY()
	UChaunceyDataContext* DataContext;
	
	UPROPERTY()
	UChaunceyRestAPI* RestAPI;
	
	UPROPERTY()
	UWebBridgeBrowser* Browser;

	UPROPERTY()
	UChaunceyWebExtension* ChaunceyExtension;

public:
	/** Publish Nodes **/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Bool(FString nodeId, bool InValue);
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_String(FString nodeId, FString InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Float(FString nodeId, float InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Integer(FString nodeId, int32 InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Vector2(FString nodeId, FVector2D InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Vector3(FString nodeId, FVector InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Vector4(FString nodeId, FVector4 InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Transform(FString nodeId, FTransform InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	void Publish_Color(FString nodeId, FLinearColor InValue);
};
