#include "Utils.h"

namespace Proto::Utils
{
    int GetIntOr(rapidjson::Value& value, const char* name, int defaultValue)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            rapidjson::Value& nestedValue = value[name];
            return nestedValue.IsInt() ? nestedValue.GetInt() : defaultValue;
        }
        else
        {
            return defaultValue;
        }
    }

    int GetFloatOr(rapidjson::Value& value, const char* name, float defaultValue)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            rapidjson::Value& nestedValue = value[name];
            return nestedValue.IsFloat() ? nestedValue.GetFloat() : defaultValue;
        }
        else
        {
            return defaultValue;
        }
    }
}