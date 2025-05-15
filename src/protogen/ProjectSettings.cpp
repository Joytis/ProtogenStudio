#include "ProjectSettings.h"
#include "Utils.h"

#include "rapidjson/document.h"

#include <filesystem>

namespace Proto
{
    void ProjectSettings::Load(rapidjson::Value& value)
    {
        panelWidth = Utils::GetIntOr(value, "PanelWidth", 0);
        panelHeight = Utils::GetIntOr(value, "PanelHeight", 0);
    }

    void ProjectSettings::Save(rapidjson::Value& value, rapidjson::Document& d)
    {
        value.AddMember("PanelWidth", panelWidth, d.GetAllocator());
        value.AddMember("PanelHeight", panelHeight, d.GetAllocator());
    }
}