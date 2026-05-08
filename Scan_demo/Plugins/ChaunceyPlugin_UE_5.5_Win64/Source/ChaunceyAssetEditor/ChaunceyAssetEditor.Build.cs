// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ChaunceyAssetEditor : ModuleRules
{
	public ChaunceyAssetEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrecompileForTargets = PrecompileTargetsType.Any;

		bUsePrecompiled = true;
		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"MainFrame",
//				"WorkspaceMenuStructure",
			});

		PrivateIncludePaths.AddRange(
			new string[] {
			});

		PublicIncludePaths.AddRange(
			new string[]
			{
				
			});

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"BlueprintGraph",
				"ChaunceyRuntime",
				"ChaunceyClient",
				"ContentBrowser",
				"Core",
				"CoreUObject",
				"DesktopWidgets",
				"EditorStyle",
				"Engine",
				"GraphEditor",
				"InputCore",
				"Kismet",
				"KismetCompiler",
				"KismetWidgets",
				"Projects",
				"PropertyEditor",
				"Slate",
				"SlateCore",
				"ToolMenus",
                "Json",
                "JsonUtilities",
                "Serialization",
                "UnrealEd",
			});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
	}
}
