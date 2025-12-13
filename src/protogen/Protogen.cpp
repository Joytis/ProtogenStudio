#include "Protogen.h"
#include "Utils.h"

PROTO_NAMESPACE

void Protogen_Update(Protogen& p, float deltaTime)
{
    // Blend between all expressions 
    // for(Vector4Grid& faceGrid : p.faceGrids)
    // {
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
    // }
}

void LoadExpressionGrid(Expression& expression)
{

}

void Protogen::LoadFromJSON(Protogen& p, rapidjson::Document& d)
{
    ZoneScoped;

    p.panelHardware = (PanelHardware)Utils::GetIntOr(d, "PanelHardware", 0);
    int width = PanelHardware_Width(p.panelHardware);
    int height = PanelHardware_Height(p.panelHardware);

    // Expressions
    if (d.HasMember("FacialRegions") && d["FacialRegions"].IsArray()) 
    {
        const rapidjson::Value& groupsArray = d["FacialRegions"];
        for(int i = 0; i < groupsArray.Size(); i++)
        {
            if(i >= PROOT_ARRAYSIZE(p.facialRegions))
            {
                continue;
            }
            
            FacialRegion& region = p.facialRegions[i];
            region.type = (FacialRegionType)i;
            region.blendMode = (BlendMode)Utils::GetIntOr(groupsArray[i], "BlendMode", 0);

            if (groupsArray[i].HasMember("Expressions") && groupsArray[i]["Expressions"].IsArray()) 
            {
                const rapidjson::Value& expressionsArray = groupsArray[i]["Expressions"];
                for(int j = 0; j < expressionsArray.Size(); j++)
                {
                    if(j >= PROOT_ARRAYSIZE(region.expressions))
                    {
                        continue;
                    }
                    
                    Expression& e = region.expressions[j];
                    region.type = (FacialRegionType)j;
                    Utils::GetStringOr(expressionsArray[j], "ImagePath", "", e.imagePath);
                }
            }
        }
    }

    // Face Panels
    if (d.HasMember("Panels") && d["Panels"].IsArray()) 
    {
        const rapidjson::Value& panelsArray = d["Panels"];
        
        p.panels.clear();
        for(int i = 0; i < panelsArray.Size(); i++)
        {
            Panel& panel = p.panels.emplace_back();
            panel.flipped = Utils::GetBoolOr(panelsArray[i], "Flipped", false);
        }
    }
}


void Protogen::SaveToJSON(Protogen& p, rapidjson::Value& o, rapidjson::Document& d)
{
    ZoneScoped;

    auto a = d.GetAllocator();
    o.AddMember("PanelHardware", (int)p.panelHardware, a);

    // Expressions
    rapidjson::Value facialRegions(rapidjson::kArrayType);
    for(const auto& region : p.facialRegions)
    {
        rapidjson::Value facialRegion(rapidjson::kObjectType);
        facialRegion.AddMember("Type", (int)region.type, a);
        facialRegion.AddMember("BlendMode", (int)region.blendMode, a);
        
        rapidjson::Value expressions(rapidjson::kArrayType);
        for(const auto& e : region.expressions)
        {
            rapidjson::Value expression(rapidjson::kObjectType);
            expression.AddMember("Type", (int)e.type, a);
            expression.AddMember("ImagePath", rapidjson::StringRef(e.imagePath), a);

            rapidjson::Value audioHeuristic(rapidjson::kObjectType);
            audioHeuristic.AddMember("Value", e.audioHeuristic.value, a);
            
            expression.AddMember("AudioHeuristic", audioHeuristic, a);
            expressions.PushBack(expression, a);
            
        }
        facialRegion.AddMember("Expressions", expressions, a);

        facialRegions.PushBack(facialRegion, a);
    }
    o.AddMember("FacialRegions", facialRegions, a);

    // Face Panels
    rapidjson::Value panels(rapidjson::kArrayType);
    for(const auto& facePanel : p.panels)
    {
        rapidjson::Value panel(rapidjson::kObjectType);
        panel.AddMember("Flipped", facePanel.flipped, a);
        panels.PushBack(panel, a);
    }
    o.AddMember("Panels", panels, a);
}

PROTO_NAMESPACE_END
