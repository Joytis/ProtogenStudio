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
    void LoadIntoGrids(std::filesystem::path& rootPath, const char* fileName, ExpressionDataVector& grids)
    {
        // Load up a bunch of expressions
        grids.clear();
        for (const auto & entry : std::filesystem::directory_iterator(rootPath))
        {
            auto directoryPath = entry.path();
            auto file = directoryPath/fileName;
    
             // Load file and decode image.
            std::vector<u8> image;
            u32 width, height;
            u32 error = lodepng::decode(image, width, height, file.string().c_str());
    
            // Expect RGB format
            assert(width * height * 4 == image.size());
            assert(error == 0);
    
            // Load the expression into memory.. As... Greyscale! I guess. 
            ExpressionData& expression = grids.emplace_back(width, height);
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

    bool ProtogenProject::IsLoaded()
    {
        return _isLoaded;
    }

    void ProtogenProject::LoadProject(std::filesystem::path& path)
    {
        auto settingsPath = path/PROJECT_SETTINGS_FILE;
        Utils::LoadFromJson<ProjectSettings>(settingsPath, _settings);

        auto expressionsPath = path/EXPRESSIONS_PATH;
        LoadIntoGrids(expressionsPath, EXPRESSION_FILE, _expressions);

        // Load up a bunch of expressions
        auto mouthPath = path/MOUTH_PATH;
        LoadIntoGrids(mouthPath, MOUTH_FILE, _mouths);
    }

    void ProtogenProject::SaveProject(std::filesystem::path& path)
    {
        auto settingsPath = path/PROJECT_SETTINGS_FILE;
        Utils::SaveToJson<ProjectSettings>(settingsPath, _settings);
    }
}