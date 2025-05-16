#pragma once

#include "rapidjson/document.h"

#include <fstream>
#include <filesystem>

namespace Proto
{
    struct ProjectSettings
    {
        int facePanelWidth;
        int facePanelHeight;
        
        void Load(rapidjson::Value& value);
        void Save(rapidjson::Value& value, rapidjson::Document& d);
    };
}