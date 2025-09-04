#include "Protogen.h"

namespace Proto
{
    void Protogen::Load(const ProjectSettings& settings)
    {
        faceGrids.clear();
        auto& grid1 = faceGrids.emplace_back(settings.facePanelWidth, settings.facePanelHeight, true);
        grid1.Fill(Color::Black);

        auto& grid2 = faceGrids.emplace_back(settings.facePanelWidth, settings.facePanelHeight, true);
        grid2.Fill(Color::Black);
    }

    void Protogen::Update(ProtogenProject& project, float deltaTime)
    {
        // Blend between all expressions 
        for(Vector4Grid& faceGrid : faceGrids)
        {
            for(const Expression& expression : project.Expressions())
            {
                assert(faceGrid.Width() == expression.grid.Width());
                assert(faceGrid.Height() == expression.grid.Height());

                int width = faceGrid.Width();
                int height = faceGrid.Height();

                // Simply iterate over the thing
                for (int y = 0; y < height; ++y) 
                {
                    for (int x = 0; x < width; ++x) 
                    {
                        // Figure out appropriate color mechanism. 
                        u8 expr = expression.grid.Get(x, y);
                        Vector4 color(expr, expr, expr, 255);
                        faceGrid.Set(x, y, color);

                        // Vector4 color((float)x / width, (float)y / height, 0.0, 1.0);
                        // faceGrid.Set(x, y, color);
                    }
                }
            }
        }
    }

}
