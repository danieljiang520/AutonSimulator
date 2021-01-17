// Copyright Epic Games, Inc. All Rights Reserved.

#include "LCM_Plugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FLCM_PluginModule"

void FLCM_PluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("LCM_Plugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath = "/usr/local/lib/liblcm.so";

// Not currently supporting platforms other than ubuntu-18.04	
// #if PLATFORM_WINDOWS
// 	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/LCM_PluginLibrary/Win64/ExampleLibrary.dll"));
// #elif PLATFORM_MAC
//     LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/LCM_PluginLibrary/Mac/Release/libExampleLibrary.dylib"));
// #endif // PLATFORM_WINDOWS

	LCMLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (LCMLibraryHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Task Failed Successfully"));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FLCM_PluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(LCMLibraryHandle);
	LCMLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLCM_PluginModule, LCM_Plugin)
