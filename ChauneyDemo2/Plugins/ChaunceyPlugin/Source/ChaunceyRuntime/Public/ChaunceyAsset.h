#pragma once

#include "ChaunceyDataRouter.h"
#include "ChaunceyTypes.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "ChaunceyAsset.generated.h"

const FName NAME_DisplayName(TEXT("DisplayName"));
const FName NAME_ScriptName(TEXT("ScriptName"));
const FName NAME_ScriptNoExport(TEXT("ScriptNoExport"));
const FName NAME_DeprecatedFunction(TEXT("DeprecatedFunction"));
const FName NAME_BlueprintGetter(TEXT("BlueprintGetter"));
const FName NAME_BlueprintSetter(TEXT("BlueprintSetter"));
const FName NAME_AllowPrivateAccess(TEXT("AllowPrivateAccess"));

/**
 * Implements an asset that binds an exposed property to a Chauncey channel
 */

USTRUCT(BlueprintType)
struct FSubscribeDelegateHandleInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FName subName;

	FDelegateHandle handle;
};

USTRUCT(BlueprintType)
struct FSubscribeBindingInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "BindingAsset")
	FName SnapshotId;
	UPROPERTY(BlueprintReadOnly, Category = "BindingAsset")
	FName ChannelId;
	UPROPERTY(BlueprintReadOnly, Category = "BindingAsset")
	FString ClassPath;
	UPROPERTY(BlueprintReadOnly, Category = "BindingAsset")
	FString FunctionName;
};


USTRUCT(BlueprintType)
struct FPublishBindingInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Id;
	UPROPERTY()
	FString Label;
	UPROPERTY()
	FGuid nodeId;
};

USTRUCT(BlueprintType)
struct FOnClientConnectBindingInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString SnapshotId;
	UPROPERTY(BlueprintReadOnly, Category = "BindingAsset")
	FString ClassPath;
	UPROPERTY(BlueprintReadOnly, Category = "BindingAsset")
	FString FunctionName;
};


DECLARE_DELEGATE_OneParam( FChaunceyBindingRefreshedDelegate, bool);

class FChaunceyBindingAssetCallbackHandler
{
public:
	void HandleChannelInput(const FString& ChannelID, const FString& ClientID, TSharedPtr<FJsonObject> Data) const;
	void HandleClientConnect(const FString& ClientID) const;
	void HandleClientDisconnect(const FString& ClientID) const;
	class UChaunceyAsset* Owner;
};

UCLASS(BlueprintType, hidecategories=(Object))
class CHAUNCEYRUNTIME_API UChaunceyAsset : public UObject
{
	GENERATED_BODY()

public:

	friend FChaunceyBindingAssetCallbackHandler;
	UChaunceyAsset();
	~UChaunceyAsset();
	virtual UWorld* GetWorld() const override;

	// We need a custom World set here because BindingAsset won't be initialized with an actor Outer
	// And therefore it's GetWorld calls will always result in null
	void SetWorld(UWorld* InWorld);

	//~ Begin UObject interface
	virtual void Serialize(FArchive& Ar) override;
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
	virtual void BeginDestroy() override;
	virtual void PostRename(UObject* OldOuter, const FName OldName) override;
	//~ End UObject interface

	void SetWorkspace(const FChaunceyWorkspace& InWorkspace);
	void SetProject(const FChaunceyProject& InProject);
	void SetSnapshot(const FChaunceySnapshot& InSnapshot);

	void AddSubscribeBinding(const TPair<FName, FName>& SnapshotIdAndChannelId, const FString& ClassPath, const FName& FunctionName);
	void SubscribeChannel(const FString& ChannelID);

	void AddOnClientConnectBinding(const FString& SnapshotID, const FString& ClassPath, const FName& FunctionName);
	void AddOnClientDisconnectBinding(const FString& SnapshotID, const FString& ClassPath, const FName& FunctionName);

	void AddPublishBinding(const TPair<FName, FName>& ChannelIdAndLabel, FGuid nodeId);
	// void OnBoolPropertyChange(TPair<FName, FName> ChannelIdAndSystemLabel, bool InBool);
	void ClearBindings();
	void UnsubscribeAll();
	void TryConnect();
	void Disconnect();

	void RunTimeSubscribeChannels();
	void RunTimeSubscribeConnectEvents(const FString& SnapshotID);
	void ClearConnectionEvents(const FString& SnapshotID);

	void AddBindingAssetActor(AActor* Actor);
	void AddConnectionEventActor(AActor* Actor);
	void AddDisconnectionEventActor(AActor* Actor);
	void RefreshData(FChaunceyBindingRefreshedDelegate Callback);

	void SetupDataRouter();
	UChaunceyDataRouter* GetDataRouter() const
	{
		return DataRouter;
	}

	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString APIKey;
	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString APIKeyId;
	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString APIKeyLabel;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TObjectPtr<class UEdGraph> EdGraph;
#endif
	
	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString SelectedWorkspaceID;
	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString SelectedWorkspaceLabel;
	
	// // New properties
	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString SelectedProjectID;
	// UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	// FString SelectedProjectLabel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Chauncey")
	TSoftObjectPtr<UChaunceySettingsProfile> SettingsProfile;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BindingAsset")
	FString ConnectionTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BindingAsset")
	FChaunceyWorkspace Workspace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BindingAsset")
	FChaunceyProject Project;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BindingAsset")
	FChaunceySnapshot Snapshot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BindingAsset")
	TArray<FString> SubscribedChannels;
	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<FSubscribeBindingInfo> SubscribeBindings;

	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<FPublishBindingInfo> PublishBindings;

	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<FOnClientConnectBindingInfo> OnClientConnectBindingInfos;

	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<FOnClientConnectBindingInfo> OnClientDisconnectBindingInfos;

	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<AActor*> BindingAssetActors;

	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<AActor*> ConnectionEventActors;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "BindingAsset")
	TArray<AActor*> DisconnectionEventActors;
private:

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& Event) override;
#endif

	FChaunceyBindingAssetCallbackHandler Handler;

	TArray<FSubscribeDelegateHandleInfo> SubscribeDelegateHandles;

	UPROPERTY()
	UChaunceyDataRouter* DataRouter;

	UWorld* World;
};