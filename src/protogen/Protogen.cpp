#include "Protogen.h"

namespace Proto
{
    Protogen::Protogen(const ProjectSettings& settings)
    {
        auto& grid = faceGrids.emplace_back(settings.facePanelWidth, settings.facePanelHeight, false);
        grid.Fill(Color::Black);

        grid = faceGrids.emplace_back(settings.facePanelWidth, settings.facePanelHeight, true);
        grid.Fill(Color::Black);
    }

    void Protogen::Update(ProtogenProject& project, float deltaTime)
    {
        // Update the face grids

        // Blend between all expressions 
        // TODO: Actually blend. Right now, we're just blanket applying them. 
        for(Vector4Grid& faceGrid : faceGrids)
        {
            for(const Expression& expression : project.Expressions())
            {
                const auto& grid = expression.grid;
                assert(faceGrid.Width() == grid.Width());
                assert(faceGrid.Height() == grid.Height());
            }
        }
    }

}
