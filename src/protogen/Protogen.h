#pragma once

#include "Grid.h"
#include "ProjectSettings.h"
#include "ProtogenProject.h"
#include "Vector4.h"

#include <vector>
#include <memory>

namespace Proto
{
    struct Protogen
    {
        using Vector4GridList = std::vector<Vector4Grid>;

        void Load(const ProjectSettings& settings);
        void Update(ProtogenProject& project, float deltaTime);

        Vector4GridList faceGrids;
    };
}