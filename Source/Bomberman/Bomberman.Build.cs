// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Bomberman : ModuleRules
{
	public Bomberman(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"HeadMountedDisplay", 
			"UMG",
			"SlateCore",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem"
		});
	}
}
