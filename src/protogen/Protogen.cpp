#include "Protogen.h"
#include "Utils.h"

namespace Proto
{
    void Protogen_Update(Protogen& p, float deltaTime)
    {
        // Blend between all expressions 
        for(Vector4Grid& faceGrid : p.faceGrids)
        {
            // for(const auto& expression : project.Expressions())
            // {
            //     assert(faceGrid.Width() == expression.grid.Width());
            //     assert(faceGrid.Height() == expression.grid.Height());

            //     int width = faceGrid.Width();
            //     int height = faceGrid.Height();

            //     // Simply iterate over the thing
            //     for (int y = 0; y < height; ++y) 
            //     {
            //         for (int x = 0; x < width; ++x) 
            //         {
            //             // Figure out appropriate color mechanism. 
            //             u8 expr = expression.grid.Get(x, y);
            //             Vector4 color(expr, expr, expr, 255);
            //             faceGrid.Set(x, y, color);

            //             // Vector4 color((float)x / width, (float)y / height, 0.0, 1.0);
            //             // faceGrid.Set(x, y, color);
            //         }
            //     }
            // }

            // for(const auto& mouth : project.Mouths())
            // {
            //     assert(faceGrid.Width() == mouth.grid.Width());
            //     assert(faceGrid.Height() == mouth.grid.Height());

            //     int width = faceGrid.Width();
            //     int height = faceGrid.Height();

            //     // Simply iterate over the thing
            //     for (int y = 0; y < height; ++y) 
            //     {
            //         for (int x = 0; x < width; ++x) 
            //         {
            //             // Figure out appropriate color mechanism. 
            //             u8 expr = mouth.grid.Get(x, y);
            //             Vector4 oldColor = faceGrid.Get(x, y);
            //             Vector4 newColor(expr, expr, expr, 255);

            //             Vector4 maxColor(
            //                 std::max(oldColor.x, newColor.x),
            //                 std::max(oldColor.y, newColor.y),
            //                 std::max(oldColor.z, newColor.z),
            //                 std::max(oldColor.w, newColor.w));

            //             faceGrid.Set(x, y, maxColor);

            //             // Vector4 color((float)x / width, (float)y / height, 0.0, 1.0);
            //             // faceGrid.Set(x, y, color);
            //         }
            //     }
            // }
        }
    }

    Protogen Protogen::LoadFromJSON(rapidjson::Document& d)
    {
        Protogen p;
        p.facePanelWidth = Utils::GetIntOr(d, "FacePanelWidth", 64);
        p.facePanelHeight = Utils::GetIntOr(d, "FacePanelHeight", 32);


        // Create the face grids while we're here. 
        p.faceGrids.emplace_back(p.facePanelWidth, p.facePanelHeight, false);
        p.faceGrids.emplace_back(p.facePanelWidth, p.facePanelHeight, true);
        return p;
    }


    void Protogen::SaveToJSON(Protogen& p, rapidjson::Value& o, rapidjson::Document& d)
    {
        o.AddMember("FacePanelWidth", p.facePanelWidth, d.GetAllocator());
        o.AddMember("FacePanelHeight", p.facePanelHeight, d.GetAllocator());

        rapidjson::Value expressionGroups(rapidjson::kArrayType);
        for(const auto& expressionGroup : p.expressionGroups)
        {
            rapidjson::Value expression(rapidjson::kObjectType);
            // expression
            
        }
        o.AddMember("ExpressionGroups", expressionGroups, d.GetAllocator());
    }
}
