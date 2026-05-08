// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class ChaunceyClient : ModuleRules
    {
        public ChaunceyClient(ReadOnlyTargetRules Target) : base(Target)
        {
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            
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
                "DeveloperSettings",
                "Json",
                "JsonUtilities",
                "WebSockets",
                "HTTP", 
                "Engine",
                "WebBridge",
                "WebBrowser",
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
				"WebSockets",
                "WebSocketNetworking"
                // ... add private dependencies that you statically link with here ...	
                }
            );
            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
                    // ... add any modules that your module loads dynamically here ...
                }
            );
        }
    }
}
