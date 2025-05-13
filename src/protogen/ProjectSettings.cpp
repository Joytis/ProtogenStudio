#include "ProjectSettings.h"
#include "Utils.h"

#include "rapidjson/document.h"

#include <filesystem>

namespace Proto
{
    void ProjectSettings::Load(rapidjson::Document& d)
    {
        panelWidth = d["PanelWidth"].GetInt();
        panelHeight = d["PanelHeight"].GetInt();
    }

    void ProjectSettings::Save(rapidjson::Document& d)
    {
        d.AddMember("PanelWidth", panelWidth, d.GetAllocator());
        d.AddMember("PanelHeight", panelHeight, d.GetAllocator());
    }
}