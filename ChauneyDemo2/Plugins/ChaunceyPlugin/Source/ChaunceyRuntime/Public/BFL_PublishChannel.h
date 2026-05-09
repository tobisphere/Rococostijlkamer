// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"
#include "Internationalization/Text.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BFL_PublishChannel.generated.h"

/**
 * 
 */
UCLASS()
class CHAUNCEYRUNTIME_API UBFL_PublishChannel : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Bool(FString nodeId, bool InValue);
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_String(FString nodeId, FString InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Float(FString nodeId, float InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Integer(FString nodeId, int32 InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Vector2(FString nodeId, FVector2D InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Vector3(FString nodeId, FVector InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Vector4(FString nodeId, FVector4 InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Transform(FString nodeId, FTransform InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void Publish_Color(FString nodeId, FLinearColor InValue);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void AddPublishBinding(FName ChannelId, FName SystemLabel, FGuid nodeId);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void SetSnapshotId(FString id, bool bSaveGame = true);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void SetApiKey(FString apiKey);

public:
	static TMultiMap<TPair<FName, FName>, FGuid> GPublishBindings;
	static FString GChannelListID;
	static FString GApiKey;
};
