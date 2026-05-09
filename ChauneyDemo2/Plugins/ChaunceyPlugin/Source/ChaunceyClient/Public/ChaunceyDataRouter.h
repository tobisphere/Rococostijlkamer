#pragma once

#include "ChaunceySettingsProfile.h"
#include "ChaunceyTypes.h"
#include "Containers/Queue.h"
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

#include "Runtime/Core/Public/HAL/ThreadSafeBool.h"
#include "ChaunceyDataRouter.generated.h"

class IWebSocket;
class FChaunceyBindingAssetCallbackHandler;

USTRUCT(BlueprintType)
struct FNodeImage {
	GENERATED_BODY()

	FNodeImage() {
		Width = 0;
		Height = 0;
		Src = "";
		Name = "";
		FileType = "";
	}

	UPROPERTY()
	int Width;

	UPROPERTY()
	int Height;

	UPROPERTY()
	FString Src;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString FileType;
};


UENUM(BlueprintType, meta = (DisplayName="EPublishMode"))
enum class EPublishMode : uint8 {
	Network UMETA(DisplayName = "Network"),
	Local UMETA(DisplayName = "Local"),
	Both UMETA(DisplayName = "Both"),
};

namespace Chauncey
{
	enum class EMessageType { 
		Invalid, 
		Connect, 
		Subscribe, 
		Unsubscribe, 
		Publish,
		OnClientConnect,
		OffClientConnect,
		OnClientDisconnect,
		OffClientDisconnect,
		ClientConnect,
		ClientDisconnect,
	};

	struct FSocketMessage
	{
		virtual ~FSocketMessage() = default;
		virtual TSharedPtr<FJsonObject> ToJSON() const = 0;
		virtual FString ToString() const;
	};

	inline EMessageType GetMessageType(const FString Type)
	{
		if (Type == "connect")
		{
			return EMessageType::Connect;
		}
		
		if (Type == "subscribe")
		{
			return EMessageType::Subscribe;
		}

		if (Type == "unsubscribe")
		{
			return EMessageType::Unsubscribe;
		}

		if (Type == "publish")
		{
			return EMessageType::Publish;
		}

		if (Type == "on_client_connect")
		{
			return EMessageType::OnClientConnect;
		}

		if (Type == "off_client_connect")
		{
			return EMessageType::OffClientConnect;
		}

		if (Type == "on_client_disconnect")
		{
			return EMessageType::OnClientDisconnect;
		}

		if (Type == "off_client_disconnect")
		{
			return EMessageType::OffClientDisconnect;
		}

		if (Type == "client_connect")
		{
			return EMessageType::ClientConnect;
		}

		if (Type == "client_disconnect")
		{
			return EMessageType::ClientDisconnect;
		}
		return EMessageType::Invalid;
	}

	struct FSubscribeMessage final : public FSocketMessage
	{
		FString SnapshotID;
		TArray<FString> ChannelIDs;

		virtual TSharedPtr<FJsonObject> ToJSON() const override;
	};

	struct FUnsubscribeMessage final : public FSocketMessage
	{
		FString SnapshotID;
		TArray<FString> ChannelIDs;

		virtual TSharedPtr<FJsonObject> ToJSON() const override;
	};

	struct FPublishMessage final : public FSocketMessage
	{
		FString SnapshotID;
		FString ChannelID;
		FString From;
		FString To;
		TSharedPtr<FJsonObject> Data;

		virtual TSharedPtr<FJsonObject> ToJSON() const override;
	};

	struct FClientMessage final : public FSocketMessage
	{
		FString SnapshotID;
		EMessageType Type;

		virtual TSharedPtr<FJsonObject> ToJSON() const override;
	};
}

bool CHAUNCEYCLIENT_API FVectorFromChaunceyValue(const TSharedPtr<FJsonObject>* ValueData, FVector &OutVector);
bool CHAUNCEYCLIENT_API FVector2DFromChaunceyValue(const TSharedPtr<FJsonObject>* ValueData, FVector2D &OutVector);
bool CHAUNCEYCLIENT_API FVector4FromChaunceyValue(const TSharedPtr<FJsonObject>* ValueData, FVector4 &OutVector);
bool CHAUNCEYCLIENT_API FTransformFromChaunceyValue(const TSharedPtr<FJsonObject>* ValueData, FTransform &OutTransform);
bool CHAUNCEYCLIENT_API FChaunceyImageFromChaunceyValue(const TSharedPtr<FJsonObject>* ValueData, FNodeImage &OutImage);
bool CHAUNCEYCLIENT_API FLinearColorFromChaunceyValue(const TSharedPtr<FJsonObject>* ValueData, FLinearColor &OutColor);

TSharedPtr<FJsonObject> CHAUNCEYCLIENT_API ChaunceyValueFromFVector(const FVector &Value);
TSharedPtr<FJsonObject> CHAUNCEYCLIENT_API ChaunceyValueFromFVector2D(const FVector2D &Value);
TSharedPtr<FJsonObject> CHAUNCEYCLIENT_API ChaunceyValueFromFVector4(const FVector4 &Value);
TSharedPtr<FJsonObject> CHAUNCEYCLIENT_API ChaunceyValueFromFTransform(const FTransform &Value);
TSharedPtr<FJsonObject> CHAUNCEYCLIENT_API ChaunceyValueFromFChaunceyImage(const FNodeImage &Value);
TSharedPtr<FJsonObject> CHAUNCEYCLIENT_API ChaunceyValueFromFLinearColor(const FLinearColor &Value);


typedef TFunction< void(const FString&, const TSharedPtr<FJsonObject>&)> ChannelDataCallback;

DECLARE_DELEGATE_OneParam(FChaunceyConnectDelegate, bool);
DECLARE_DELEGATE_ThreeParams(FChaunceyDataDelegate, const FString&, const FString&, TSharedPtr<FJsonObject>);
DECLARE_EVENT_ThreeParams(UChaunceyDataRouter, FChaunceyChannelDelegate, const FString&, const FString&, TSharedPtr<FJsonObject>);
DECLARE_DELEGATE_OneParam(FChaunceyClientSubscribeDelegate, const FString&);
DECLARE_EVENT_OneParam(UChaunceyDataRouter, FChaunceyClientDelegate, const FString&);

/*
* Channel Type Delegates
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyActionEvent, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyNumberEvent, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyFloatEvent, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyIntegerEvent, int32, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyStringEvent, FString, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyBooleanEvent, bool, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyVectorEvent, FVector, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyVector2Event, FVector2D, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyVector4Event, FVector4, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyTransformEvent, FTransform, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyImageEvent, FNodeImage, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaunceyColorEvent, FLinearColor, Value);

UCLASS()
class CHAUNCEYCLIENT_API UChaunceyDataRouter: public UObject {
	GENERATED_BODY()
public:
	UChaunceyDataRouter();
	virtual ~UChaunceyDataRouter() override;

	void Connect();
	void Connect(const FString& InApiKey, const FString& InProjectId, const FString& InSnapshotId, const FString& InConnectionTag);
	void Disconnect(bool InWantsReconnect = false);

	void Publish(const FString &SnapshotID, const FString& ChannelID, TSharedPtr<FJsonObject> Data, const FString& ToClientID = "") const;
	void PublishLocal(const FString &SnapshotID, const FString& ChannelID, const FString &ClientID, TSharedPtr<FJsonObject> Data);

	void PublishClient(const FString& SnapshotID, const Chauncey::EMessageType Type) const;

	void EnableConnectionEvents();
	void DisableConnectionEvents();

	void OnClientConnect(const FString& SnapshotID, const FChaunceyClientSubscribeDelegate& Callback);
	void OffClientConnect(const FString& SnapshotID, const FDelegateHandle& Callback);
	void OnClientDisconnect(const FString& SnapshotID, const FChaunceyClientSubscribeDelegate& Callback);
	void OffClientDisconnect(const FString& SnapshotID, const FDelegateHandle& Callback);
	void ClearConnectionEvents(const FString& SnapshotID);

	FDelegateHandle Subscribe(const FString& SnapshotID, const FString& ChannelID, const FChaunceyDataDelegate& Callback);
	void Unsubscribe(const FString& SnapshotID, const FString& ChannelID, const FDelegateHandle& Callback);

	void SubscribeClientConnect();
	void SubscribeClientDisconnect();
	
	FThreadSafeBool bWantsReconnect = true;
	FThreadSafeBool bConnected = false;
	FThreadSafeBool bIsConnecting = false;
	
	void SetSettingsProfile(UChaunceySettingsProfile* InSettingsProfile);

	void ReceiveProperty(const TSharedPtr<FJsonObject>& Data, FProperty* Property, UObject* PropertyOwner) const;
	void PublishBoolProperty(const FString& InSnapshotId, const FName& ChannelId, bool InBool) const;
	void PublishStringProperty(const FString& InSnapshotId, const FName& ChannelId, FString InString);
	void PublishFloatProperty(const FString& InSnapshotId, const FName& ChannelId, float InFloat);
	void PublishIntegerProperty(const FString& InSnapshotId, const FName& ChannelId, int32 InInt);
	void PublishVector2Property(const FString& InSnapshotId, const FName& ChannelId, FVector2D InVector);
	void PublishVector3Property(const FString& InSnapshotId, const FName& ChannelId, FVector InVector);
	void PublishVector4Property(const FString& InSnapshotId, const FName& ChannelId, FVector4 InVector);
	void PublishTransformProperty(const FString& InSnapshotId, const FName& ChannelId, FTransform InTransform);
	void PublishColorProperty(const FString& InSnapshotId, const FName& ChannelId, FLinearColor InColor);
	void PublishProperty(const FString& InSnapshotId, const FName& ChannelId, FProperty* Property, UObject* PropertyOwner);
	// FDelegateHandle AddDisconnectionEvent(const FString& SnapshotId, FChaunceyBindingAssetCallbackHandler* Handler);

private:
	void ReloadSettings(UChaunceySettingsProfile* InSettingsProfile);
	
	TSharedPtr<IWebSocket> Socket;

	UPROPERTY()
	UChaunceySettingsProfile* SettingsProfile;
	
	void OnConnected();
	void OnConnectionError(const FString& Error);
	void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	void OnMessage(const FString &MessageString);

	void Reconnect();
	void ProcessQueuedCommands();
	
	// Snapshot_Id -> ChannelID -> Delegate
	TMap<FString, TMap<FString, FChaunceyChannelDelegate>> Subscriptions;
	FChaunceyClientDelegate ClientConnectDelegate;
	FChaunceyClientDelegate ClientDisconnectDelegate;
	
	TQueue<FString> Commands;

	FString ClientID = "";
	FString ApiKey = "";
	FString ConnectionTag = "";

	FString ProjectId = "";
	FString SnapshotId = "";

	// FCriticalSection ConnectLock;
	// FCriticalSection SubscribeLock;

	TMap<FString, FChaunceySnapshot> LoadedSnapshots;
};
