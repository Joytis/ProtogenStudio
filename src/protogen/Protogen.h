#pragma once

#include "Grid.h"

#include <vector>
#include <array>
#include <memory>

PROTO_NAMESPACE

constexpr u32 PROTO_MAX_PATH_LEN = 256;

struct AudioHeuristic
{
    float value = 0.0f;
};

struct Expression
{
    // Serialized
    ExpressionType type = ExpressionType::Happy;
    char imagePath[PROTO_MAX_PATH_LEN] = "";
    bool editorTreeFoldedOut = false;
    AudioHeuristic audioHeuristic;
    
    // Not serialized 
    Grid grid;
};


struct FacialRegion
{
    // Serialized
    FacialRegionType type = FacialRegionType::Mouth;
    BlendMode blendMode  = BlendMode::BestFit;
    bool editorTreeFoldedOut = false;
    Expression expressions[(int)ExpressionType::MAX];
};

struct Panel
{
    // Serialized
    bool editorTreeFoldedOut = false;
    bool flipped = false;

    // Non Serialized
    Grid grid;
};

struct Protogen
{
    PanelHardware panelHardware = PanelHardware::AdaFruitLED64x32;
    
    FacialRegion facialRegions[(int)FacialRegionType::MAX];
    std::vector<Panel> panels;

    int PanelWidth() { return PanelHardware_Width(panelHardware); }
    int PanelHeight() { return PanelHardware_Height(panelHardware); }

    static void LoadFromJSON(Protogen& p, rapidjson::Document& d);
    static void SaveToJSON(Protogen& p, rapidjson::Value& o, rapidjson::Document& d);
};

PROTO_NAMESPACE_END
