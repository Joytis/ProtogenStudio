#include "Utils.h"

namespace Proto::Utils
{
    int GetIntOr(const rapidjson::Value& value, const char* name, int defaultValue)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            const rapidjson::Value& nestedValue = value[name];
            return nestedValue.IsInt() ? nestedValue.GetInt() : defaultValue;
        }
        else
        {
            return defaultValue;
        }
    }

    int GetFloatOr(const rapidjson::Value& value, const char* name, float defaultValue)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            const rapidjson::Value& nestedValue = value[name];
            return nestedValue.IsFloat() ? nestedValue.GetFloat() : defaultValue;
        }
        else
        {
            return defaultValue;
        }
    }

    void GetStringOr(const rapidjson::Value& value, const char* name, const char* defaultValue, char* dest, u32 size)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            const rapidjson::Value& nestedValue = value[name];
            const char* internalString = nestedValue.IsString() ? nestedValue.GetString() : defaultValue;
            memcpy(dest, defaultValue, Math::Minimum((u32)nestedValue.GetStringLength(), (u32)size));
        }
        else
        {
            memcpy(dest, defaultValue, Math::Minimum((u32)strlen(defaultValue), (u32)size));
        }
    }

    template<u32 TSize>
    void GetStringOr(const rapidjson::Value& value, const char* name, const char* defaultValue, char (&dest)[TSize])
    {
        GetStringOr(value, name, defaultValue, &dest[0], TSize);
    }

    std::string GetStringOr(const rapidjson::Value& value, const char* name, const char* defaultValue)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            const rapidjson::Value& nestedValue = value[name];
            return nestedValue.IsString() ? nestedValue.GetString() : defaultValue;
        }
        else
        {
            return defaultValue;
        }
    }

    bool GetBoolOr(const rapidjson::Value& value, const char* name, bool defaultValue)
    {
        if(value.HasMember(name) && value.IsObject())
        {
            const rapidjson::Value& nestedValue = value[name];
            return nestedValue.IsBool() ? nestedValue.GetBool() : defaultValue;
        }
        else
        {
            return defaultValue;
        }
    }

}