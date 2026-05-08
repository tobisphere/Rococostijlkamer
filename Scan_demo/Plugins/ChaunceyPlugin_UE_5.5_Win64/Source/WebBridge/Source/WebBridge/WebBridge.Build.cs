// Copyright 2023, Ryan Shetley. All Rights Reserved.

using UnrealBuildTool;

public class WebBridge : ModuleRules
{
	public WebBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrecompileForTargets = PrecompileTargetsType.Any;
		
		bUsePrecompiled = true;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"WebBrowser",
				"Slate",
				"SlateCore",
				"UMG",
				"Json", 
				"JsonUtilities"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"WebBrowser",
				"Json",
				"JsonUtilities"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		if (Target.bBuildEditor || Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.IOS)
		{
			// WebBrowserTexture required for cooking Android
			PrivateIncludePathModuleNames.AddRange(
				new string[]
				{
					"WebBrowserTexture",
				}
			);
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"WebBrowserTexture",
				}
			);
		}

		if (Target.Platform == UnrealTargetPlatform.Win64
		    || Target.Platform == UnrealTargetPlatform.Mac
		    || Target.Platform == UnrealTargetPlatform.Linux)
		{
			PrivateDefinitions.Add("USING_CEF_SHARED=1");
			PrivateDependencyModuleNames.Add("CEF3Utils");
			AddEngineThirdPartyPrivateStaticDependencies(Target,
				"CEF3"
			);
		}
	}
}
