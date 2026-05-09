// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaunceySettingsProfile.h"

#include "ChaunceyTypes.h"
#include "ChaunceyRestAPI.generated.h"

DECLARE_DELEGATE_OneParam(FChaunceyLoginDelegate, bool);
DECLARE_DELEGATE_TwoParams(FChaunceyGetWorkspacesDelegate, bool, const TArray<FChaunceyWorkspace>&);
DECLARE_DELEGATE_TwoParams(FChaunceyGetWorkspaceDelegate, bool, const FChaunceyWorkspace&);
DECLARE_DELEGATE_TwoParams(FChaunceyGetProjectsDelegate, bool, const TArray<FChaunceyProject>&);
DECLARE_DELEGATE_TwoParams(FChaunceyGetSnapshotsDelegate, bool, const TArray<FChaunceySnapshot>&);

// TODO: clean this up to use a better structure
DECLARE_DELEGATE_TwoParams(FChaunceyGetSnapshotDelegate, bool, const FChaunceySnapshot&);

UCLASS()
class CHAUNCEYCLIENT_API UChaunceyRestAPI : public UObject
{
	GENERATED_BODY()
public:
	UChaunceyRestAPI();
	
	void GetWorkspaces(FChaunceyGetWorkspacesDelegate Callback) const;
	void GetWorkspace(const FString& WorkspaceID, FChaunceyGetWorkspaceDelegate Callback) const;

	void GetProjects(const FString& WorkspaceID, FChaunceyGetProjectsDelegate Callback) const;
	
	void GetSnapshots(const FString& ProjectID, FChaunceyGetSnapshotsDelegate Callback) const;
	void GetSnapshot(const FString& ProjectID, const FString SnapshotID, FChaunceyGetSnapshotDelegate Callback) const;
	
	void SetSettingsProfile(UChaunceySettingsProfile* InSettingsProfile);
private:
	UPROPERTY()
	UChaunceySettingsProfile* SettingsProfile;
	FChaunceyGetWorkspacesDelegate OnGetWorkspacesComplete;
	FChaunceyGetWorkspaceDelegate OnGetWorkspaceComplete;
	FChaunceyGetProjectsDelegate OnGetProjectsComplete;
	FChaunceyGetSnapshotsDelegate OnGetSnapshotsComplete;
	FChaunceyGetSnapshotDelegate OnGetSnapshotComplete;
};
