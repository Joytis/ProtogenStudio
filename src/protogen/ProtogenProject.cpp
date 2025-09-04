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

            // Expect RGB format
            assert(width * height * 4 == image.size());
            assert(error == 0);

            // Load the expression into memory.. As... Greyscale! I guess. 
            Expression& expression = _expressions.emplace_back(rootExpresisonPath, width, height);
            expression.grid.Fill(0);

            for(int y = 0; y < height; y++)
            {
                for(int x = 0; x < width; x++)
                {
                    int baseIndex = (y * (width * 4) + (x * 4));
                    expression.grid.Set(x, y, image[baseIndex]);
                }
            }
        }
    }

    void ProtogenProject::SaveProject(std::filesystem::path& path)
    {
        auto settingsPath = path/PROJECT_SETTINGS_FILE;
        Utils::SaveToJson<ProjectSettings>(settingsPath, _settings);
    }
}