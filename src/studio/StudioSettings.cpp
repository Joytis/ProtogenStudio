

namespace Studio
{

    struct Settings
    {
        char lastProjectPath[512];
        int lastWindowWidth;
        int lastWindowHeight;

        static Settings LoadFromJSON(rapidjson::Document& d)
        {

        }
        static void SaveToJSON(Settings& settings, rapidjson::Value& o, rapidjson::Document& d)
        {

        }
    };

    void LoadSettings(Settings& settings);

    void SaveSettings(Settings& settings);


}
