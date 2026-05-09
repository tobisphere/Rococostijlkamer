#pragma once

#include "GameFramework/Actor.h"
#include "Dom/JsonObject.h"
#include "ChaunceyActor.generated.h"

UCLASS(hideCategories = (Rendering, Physics, LOD, Activation, Input, Replication, Collision, Actor, Cooking))
class CHAUNCEYRUNTIME_API AChaunceyActor
 : public AActor
{
public:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="General")
	class UChaunceyAsset* Asset;

	virtual void PostRegisterAllComponents() override;

private:
	FDelegateHandle OnPublishEventHandle;
	void OnPublishEvent(const FGuid& InGuid, TSharedPtr<FJsonObject> InObject);
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};