#pragma once

#include "rapidjson/document.h"

namespace Proto
{
    struct Vector4
    {
        float x, y, z, w;
    
        constexpr Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
        constexpr Vector4(float _x, float _y, float _z, float _w)  : x(_x), y(_y), z(_z), w(_w) { }

        void Load(rapidjson::Value& value);
        void Save(rapidjson::Value& value);
    };

    namespace Color
    {
        static constexpr Vector4 Black = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        static constexpr Vector4 White = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        static constexpr Vector4 Red = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
        static constexpr Vector4 Blue = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
        static constexpr Vector4 Green = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
    }

}