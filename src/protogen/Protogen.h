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
        char name[PROTO_MAX_PATH_LEN] = "";
        AudioHeuristic audioHeuristic;
        Grid<u8> grid;
    };

    struct ExpressionGroup
    {
        char name[PROTO_MAX_PATH_LEN] = "";
        BlendMode blendMode  = BlendMode::BestFit;
        std::vector<Expression> expressions;
    };
    
    struct Protogen
    {
        int facePanelWidth;
        int facePanelHeight;
    
        std::vector<ExpressionGroup> expressionGroups;
        std::vector<Vector4Grid> faceGrids;
    };

}