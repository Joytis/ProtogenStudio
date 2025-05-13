#include "ProtogenProject.h"
#include "Utils.h"

#include <iostream>

namespace
{
    constexpr const char* PROJECT_SETTINGS_FILE = "ProjectSettings.json";
}

namespace Proto
{
    bool ProtogenProject::IsLoaded()
    {
        return _isLoaded;
    }

    void ProtogenProject::LoadProject(std::filesystem::path& path)
    {
        auto settingsPath = path/PROJECT_SETTINGS_FILE;
        Utils::LoadFromJson<ProjectSettings>(settingsPath, _settings);
    }

    void ProtogenProject::SaveProject(std::filesystem::path& path)
    {
        auto settingsPath = path/PROJECT_SETTINGS_FILE;
        Utils::SaveToJson<ProjectSettings>(settingsPath, _settings);
    }
}