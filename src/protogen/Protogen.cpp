#include "Protogen.h"

namespace Proto
{
    Protogen::Protogen(const ProjectSettings& settings)
    {
        auto grid = std::make_unique<Vector4Grid>(settings.facePanelWidth, settings.facePanelHeight, false);
        grid->Fill(Color::Black);
        faceGrids.push_back(std::move(grid));

        grid = std::make_unique<Vector4Grid>(settings.facePanelWidth, settings.facePanelHeight, true);
        grid->Fill(Color::Black);
        faceGrids.push_back(std::move(grid));
    }

}
