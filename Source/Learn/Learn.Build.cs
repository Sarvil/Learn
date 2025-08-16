// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Learn : ModuleRules
{
	public Learn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks"
        });

		PublicIncludePaths.AddRange(new string[] {
			"Learn",
			"Learn/Variant_Platforming",
			"Learn/Variant_Platforming/Animation",
			"Learn/Variant_Combat",
			"Learn/Variant_Combat/AI",
			"Learn/Variant_Combat/Animation",
			"Learn/Variant_Combat/Gameplay",
			"Learn/Variant_Combat/Interfaces",
			"Learn/Variant_Combat/UI",
			"Learn/Variant_SideScrolling",
			"Learn/Variant_SideScrolling/AI",
			"Learn/Variant_SideScrolling/Gameplay",
			"Learn/Variant_SideScrolling/Interfaces",
			"Learn/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
