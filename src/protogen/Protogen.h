#pragma once

#include "Grid.h"
#include "ProjectSettings.h"
#include "Vector4.h"

#include <vector>
#include <memory>

namespace Proto
{
    struct Protogen
    {
        using Vector4GridList = std::vector<std::unique_ptr<Vector4Grid>>;

        Protogen(const ProjectSettings& settings);

        Vector4GridList faceGrids;
    };
}