#pragma once

#include "ProjectSettings.h"
#include <filesystem>

namespace Proto
{
    class ProtogenProject
    {
    public:

        bool IsLoaded();
        void LoadProject(std::filesystem::path& path);
        void SaveProject(std::filesystem::path& path);

        ProjectSettings& Settings() { return _settings; }

    private:

        bool _isLoaded = false;
        ProjectSettings _settings;

        
    };
}