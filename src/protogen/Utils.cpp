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
}