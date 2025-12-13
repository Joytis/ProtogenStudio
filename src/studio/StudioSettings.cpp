

namespace Studio
{

    struct StudioSettings
    {
        std::string lastRootPath;
        std::string lastProjectPath;
        int lastWindowWidth;
        int lastWindowHeight;
        int lastWindowX;
        int lastWindowY;

        static void LoadFromJSON(StudioSettings& settings, rapidjson::Document& d)
        {
            using namespace Proto;

            StudioSettings s;
            s.lastProjectPath = Utils::GetStringOr(d, "LastProjectPath", "");
            s.lastWindowWidth = Utils::GetIntOr(d, "LastWindowWidth", 800);
            s.lastWindowHeight = Utils::GetIntOr(d, "LastWindowHeight", 600);
            s.lastWindowX = Utils::GetIntOr(d, "LastWindowX", 200);
            s.lastWindowY = Utils::GetIntOr(d, "LastWindowY", 200);
        }

        static void SaveToJSON(StudioSettings& settings, rapidjson::Value& o, rapidjson::Document& d)
        {
            o.AddMember("LastProjectPath", settings.lastProjectPath, d.GetAllocator());
            o.AddMember("LastWindowWidth", settings.lastWindowWidth, d.GetAllocator());
            o.AddMember("LastWindowHeight", settings.lastWindowHeight, d.GetAllocator());
            o.AddMember("LastWindowX", settings.lastWindowX, d.GetAllocator());
            o.AddMember("LastWindowY", settings.lastWindowY, d.GetAllocator());
        }
    };
}
