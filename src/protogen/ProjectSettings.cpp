#include "ProjectSettings.h"
#include "Utils.h"

namespace Proto
{
    void ProjectSettings::Load(rapidjson::Value& value)
    {
        facePanelWidth = Utils::GetIntOr(value, "FacePanelWidth", 0);
        facePanelHeight = Utils::GetIntOr(value, "FacePanelHeight", 0);
    }

    void ProjectSettings::Save(rapidjson::Value& value, rapidjson::Document& d)
    {
        value.AddMember("FacePanelWidth", facePanelWidth, d.GetAllocator());
        value.AddMember("FacePanelHeight", facePanelHeight, d.GetAllocator());
    }
}