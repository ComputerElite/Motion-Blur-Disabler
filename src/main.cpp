#include "main.hpp"
#include "GlobalNamespace/SaberTrail.hpp"

#include "UnityEngine/Transform.hpp"

using namespace GlobalNamespace;

static ModInfo modInfo;
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

MAKE_HOOK_OFFSETLESS(SaberTrail_LateUpdate, void, SaberTrail* self) {
  // Do stuff when this function is called  
  self->whiteSectionMaxDuration = 0.0f;
  SaberTrail_LateUpdate(self);
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

extern "C" void load() {
    getLogger().info("Installing hooks...");
    il2cpp_functions::Init();
    // Install our hooks
    LoggerContextObject logger = getLogger().WithContext("load");
    INSTALL_HOOK_OFFSETLESS(logger, SaberTrail_LateUpdate, il2cpp_utils::FindMethodUnsafe("", "SaberTrail", "LateUpdate", 0));
    getLogger().info("Installed all hooks!");
}