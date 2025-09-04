#include "ProtogenProject.h"
#include "Utils.h"

namespace
{
    constexpr const char* PROJECT_SETTINGS_FILE = "ProjectSettings.json";
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

        // Load up a bunch of expressions
        auto expressionsPath = path/EXPRESSIONS_PATH;
        for (const auto & entry : std::filesystem::directory_iterator(expressionsPath))
        {
            auto rootExpresisonPath = entry.path();
            auto expressionFile = rootExpresisonPath/EXPRESSION_FILE;

             // Load file and decode image.
            std::vector<u8> image;
            u32 width, height;
            u32 error = lodepng::decode(image, width, height, expressionFile.string().c_str());
            
            Expression& expression = _expressions.emplace_back(rootExpresisonPath, width, height);

            // If there's an error, display it.
            std::cout << width << ", " << height << ", " << image.size() << std::endl;
        }
    }

    void ProtogenProject::SaveProject(std::filesystem::path& path)
    {
        auto settingsPath = path/PROJECT_SETTINGS_FILE;
        Utils::SaveToJson<ProjectSettings>(settingsPath, _settings);
    }
}