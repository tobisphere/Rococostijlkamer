#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "ChaunceyAsset.h"

DECLARE_LOG_CATEGORY_EXTERN(LogChaunceyRuntime, Log, All);

class FChaunceyRuntimeModule : public IModuleInterface
{
public:
	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static FChaunceyRuntimeModule& Get()
	{
		static const FName ModuleName = "ChaunceyRuntime";
		return FModuleManager::LoadModuleChecked<FChaunceyRuntimeModule>(ModuleName);
	}

	void StartupModule() override;
	void ShutdownModule() override;
	bool SupportsDynamicReloading() override;

	bool RegisterAsset(FName Name, class UChaunceyAsset* Asset);
	void UnregisterAsset(FName Name);
	//
	// void LoadAllBindingAssets();
};