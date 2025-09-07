#pragma once

#include "Grid.h"
#include "Vector4.h"

#include <vector>
#include <memory>

namespace Proto
{
    constexpr u32 PROTO_MAX_PATH_LEN = 256;

    enum class BlendMode
    {
        BestFit,
        FullBlend,
    };

    struct AudioHeuristic
    {
        float value = 0.0f;
    };

    struct Expression
    {
        Expression(int width, int height) : grid(width, height, false) {}

        char name[PROTO_MAX_PATH_LEN] = "";
        bool nameOpen = false; // This is really only used on the Studio UI... but fuck it. 
        AudioHeuristic audioHeuristic;
        Grid<u8> grid;
    };

    struct ExpressionGroup
    {
        char name[PROTO_MAX_PATH_LEN] = "";
        bool nameOpen = false; // This is really only used on the Studio UI... but fuck it. 
        BlendMode blendMode  = BlendMode::BestFit;
        std::vector<Expression> expressions;
    };
    
    struct Protogen
    {
        int facePanelWidth;
        int facePanelHeight;
    
        std::vector<ExpressionGroup> expressionGroups;
        std::vector<Vector4Grid> faceGrids;

        static Protogen LoadFromJSON(rapidjson::Document& d);
        static void SaveToJSON(Protogen& p, rapidjson::Value& o, rapidjson::Document& d);
    };

}