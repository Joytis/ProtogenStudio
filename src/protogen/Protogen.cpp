#include "Protogen.h"
#include "Utils.h"

namespace Proto
{
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

    Protogen Protogen::LoadFromJSON(rapidjson::Document& d)
    {
        Protogen p;
        p.panelHardware = (PanelHardware)Utils::GetIntOr(d, "PanelHardware", 0);
        int width = PanelHardware_Width(p.panelHardware);
        int height = PanelHardware_Height(p.panelHardware);

        // Expressions
        if (d.HasMember("ExpressionGroups") && d["ExpressionGroups"].IsArray()) 
        {
            const rapidjson::Value& groupsArray = d["ExpressionGroups"];
            for(int i = 0; i < groupsArray.Size(); i++)
            {
                ExpressionGroup& group = p.expressionGroups.emplace_back();
                Utils::GetStringOr(groupsArray[i], "Name", "group", group.name);
                group.blendMode = (BlendMode)Utils::GetIntOr(groupsArray[i], "BlendMode", 0);

                if (groupsArray[i].HasMember("Expressions") && groupsArray[i]["Expressions"].IsArray()) 
                {
                    const rapidjson::Value& expressionsArray = groupsArray[i]["Expressions"];
                    for(int i = 0; i < expressionsArray.Size(); i++)
                    {
                        Expression& e = group.expressions.emplace_back(width, height);
                        Utils::GetStringOr(expressionsArray[i], "Name", "expression", e.name);
                        Utils::GetStringOr(expressionsArray[i], "ImagePath", "", e.imagePath);

                        int audio = Utils::GetIntOr(expressionsArray[i], "AudioHeuristic", 0);
                        e.audioHeuristic = (AudioHeuristic)audio;
                    }
                }
            }
        }
    
        // Face Panels
        if (d.HasMember("Panels") && d["Panels"].IsArray()) 
        {
            const rapidjson::Value& panelsArray = d["Panels"];
            for(int i = 0; i < panelsArray.Size(); i++)
            {
                Panel& panel = p.panels.emplace_back();
                panel.flipped = Utils::GetBoolOr(panelsArray[i], "Flipped", false);
            }
        }

        return p;
    }


    void Protogen::SaveToJSON(Protogen& p, rapidjson::Value& o, rapidjson::Document& d)
    {
        auto a = d.GetAllocator();
        o.AddMember("PanelHardware", (int)p.panelHardware, a);

        // Expressions
        rapidjson::Value expressionGroups(rapidjson::kArrayType);
        for(const auto& group : p.expressionGroups)
        {
            rapidjson::Value expressionGroup(rapidjson::kObjectType);
            expressionGroup.AddMember("Name", rapidjson::StringRef(group.name), a);

            int blendMode = static_cast<int>(group.blendMode);
            expressionGroup.AddMember("BlendMode", blendMode, a);
            
            rapidjson::Value expressions(rapidjson::kArrayType);
            for(const auto& e : group.expressions)
            {
                rapidjson::Value expression(rapidjson::kObjectType);
                expression.AddMember("Name", rapidjson::StringRef(e.name), a);
                expression.AddMember("ImagePath", rapidjson::StringRef(e.imagePath), a);

                rapidjson::Value audioHeuristic(rapidjson::kObjectType);
                audioHeuristic.AddMember("Value", e.audioHeuristic.value, a);
                
                expression.AddMember("AudioHeuristic", audioHeuristic, a);
                expressions.PushBack(expression, a);
                
            }
            expressionGroup.AddMember("Expressions", expressions, a);

            expressionGroups.PushBack(expressionGroup, a);
        }
        o.AddMember("ExpressionGroups", expressionGroups, a);

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
}
