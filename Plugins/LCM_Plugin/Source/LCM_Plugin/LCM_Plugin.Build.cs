// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class LCM_Plugin : ModuleRules
{
	public LCM_Plugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"/usr/local/lib",
				"$(PluginDir)/Source/ThirdParty/lcm"
			}
			);	
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
				// ... add other public dependencies that you statically link with here ...
			}
			);	

		PublicAdditionalLibraries.Add("/usr/local/lib/liblcm.so");
	}
}
