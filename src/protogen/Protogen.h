#pragma once

#include "Grid.h"

#include <vector>
#include <memory>

PROTO_NAMESPACE

constexpr u32 PROTO_MAX_PATH_LEN = 256;

struct AudioHeuristic
{
    float value = 0.0f;
};

struct Expression
{
    Expression(int width, int height) : grid(width, height, false) {}

    // Serialized
    char name[PROTO_MAX_PATH_LEN] = "";
    char imagePath[PROTO_MAX_PATH_LEN] = "";
    AudioHeuristic audioHeuristic;
    
    // Not serialized 
    bool nameOpen = false; // This is really only used on the Studio UI... but fuck it. 
    Grid grid;
};

struct ExpressionGroup
{
    // Serialized
    char name[PROTO_MAX_PATH_LEN] = "";
    BlendMode blendMode  = BlendMode::BestFit;
    std::vector<Expression> expressions;

    // Not serialized 
    bool nameOpen = false; // This is really only used on the Studio UI... but fuck it. 
};

struct Panel
{
    // Serialized
    bool flipped;

    // Non Serialized
    Grid grid;
};

struct Protogen
{
    PanelHardware panelHardware = PanelHardware::AdaFruitLED64x32;
    
    std::vector<ExpressionGroup> expressionGroups;
    std::vector<Panel> panels;

    int PanelWidth() { return PanelHardware_Width(panelHardware); }
    int PanelHeight() { return PanelHardware_Height(panelHardware); }

    static Protogen LoadFromJSON(rapidjson::Document& d);
    static void SaveToJSON(Protogen& p, rapidjson::Value& o, rapidjson::Document& d);
};

PROTO_NAMESPACE_END
