// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ChaunceyRuntime : ModuleRules
	{
		public ChaunceyRuntime(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
			
			PrecompileForTargets = PrecompileTargetsType.Any;

		bUsePrecompiled = true;
			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
					"HTTPServer"
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
					"Json",
					"JsonUtilities",
					"Serialization",
					"HTTPServer",
					"ChaunceyClient"
				});
            
			if (Target.bBuildEditor)
			{
				PrivateDependencyModuleNames.AddRange(
					new string[] {
						"UnrealEd",
					}
				);
			}
		}
	}
}
