#pragma once

#include "rapidjson/document.h"

#include <fstream>
#include <filesystem>

namespace Proto
{
    struct ProjectSettings
    {
        int panelWidth;
        int panelHeight;
        
        void Load(rapidjson::Document& d);
        void Save(rapidjson::Document& d);
    };
}