#pragma once

#include "ProjectSettings.h"

#include <vector>
#include <filesystem>

namespace Proto
{
    struct ExpressionData
    {
        ExpressionData(int width, int height) : grid(width, height, false) {}

        Grid<u8> grid;
    };

    using ExpressionDataVector = std::vector<ExpressionData>;

    class ProtogenProject
    {
    public:

        bool IsLoaded();
        void LoadProject(std::filesystem::path& path);
        void SaveProject(std::filesystem::path& path);

        ProjectSettings& Settings() { return _settings; }

        const ExpressionDataVector& Expressions() { return _expressions; }
        const ExpressionDataVector& Mouths() { return _mouths; }

    private:

        bool _isLoaded = false;
        ProjectSettings _settings;

        ExpressionDataVector _expressions;
        ExpressionDataVector _mouths;
    };
}