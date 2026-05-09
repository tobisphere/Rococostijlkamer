// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaunceyTypes.h"
#include "UObject/Object.h"
#include "ChaunceyDataContext.generated.h"

/**
 * 
 */
UCLASS()
class CHAUNCEYCLIENT_API UChaunceyDataContext : public UObject
{
	GENERATED_BODY()
public:
	void SetWorkspaces(const TArray<FChaunceyWorkspace>& InWorkspaces);
	void SetWorkspace(const FChaunceyWorkspace& InWorkspace);
	void SetProjects(const FString& InWorkspaceId, const TArray<FChaunceyProject>& InProjects);
	void SetSnapshots(const FString& InProjectId, const TArray<FChaunceySnapshot>& InSnapshots);
	
	const TArray<FChaunceyWorkspace>& GetWorkspaces() { return Workspaces; }
	const TMap<FString, TArray<FChaunceyProject>>& GetProjects() { return Projects; }
	const TMap<FString, TArray<FChaunceySnapshot>>& GetSnapshots() { return Snapshots; }
private:
	TArray<FChaunceyWorkspace> Workspaces;
	TMap<FString, TArray<FChaunceyProject>> Projects;
	TMap<FString, TArray<FChaunceySnapshot>> Snapshots;
};
