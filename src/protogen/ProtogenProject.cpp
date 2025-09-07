#include "ProtogenProject.h"
#include "Utils.h"

namespace
{
    constexpr const char* EXPRESSIONS_PATH = "expressions";
    constexpr const char* EXPRESSION_FILE = "expression.png";
    constexpr const char* MOUTH_PATH = "mouth";
    constexpr const char* MOUTH_FILE = "mouth.png";

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