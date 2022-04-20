// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class cryptotest : ModuleRules
{
	public cryptotest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "UMG", "SLATECORE"
		});
		PrivateDependencyModuleNames.AddRange(new string[] {"Http", "Json", "JsonUtilities", "WebBrowserWidget", "OnlineSubsystem", "OnlineSubsystemEOS", "OnlineSubsystemEOSPlus", "OnlineSubsystemUtils", "OnlineSubsystemNull"});
	}
}