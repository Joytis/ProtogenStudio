#include "Utils.h"

namespace Proto
{
    constexpr const char* PROTOGEN_FILE_NAME = "Protogen.json";

    
    Protogen LoadProtogenFromJSON(rapidjson::Value& value)
    {
        Protogen p;
        p.facePanelWidth = Utils::GetIntOr(value, "FacePanelWidth", 64);
        p.facePanelHeight = Utils::GetIntOr(value, "FacePanelHeight", 32);


        // Create the face grids while we're here. 
        p.faceGrids.emplace_back(p.facePanelWidth, p.facePanelHeight, false);
        p.faceGrids.emplace_back(p.facePanelWidth, p.facePanelHeight, true);
        return p;
    }

    void SaveProtogenToJSON(Protogen& p, rapidjson::Value& value, rapidjson::Document& d)
    {
        value.AddMember("FacePanelWidth", p.facePanelWidth, d.GetAllocator());
        value.AddMember("FacePanelHeight", p.facePanelHeight, d.GetAllocator());

        rapidjson::Value expressionGroups(rapidjson::kArrayType);
        for(const auto& expressionGroup : p.expressionGroups)
        {
            rapidjson::Value expression(rapidjson::kObjectType);
            // expression
            
        }
        value.AddMember("ExpressionGroups", expressionGroups, d.GetAllocator());
        // value.Add
    }

    enum class LoadResult
    {
        Success,
        JsonError,
        FileDoesNotExist,
    };

    struct ProtogenLoadResult
    {
        LoadResult result;
        std::string message;
    };

    ProtogenLoadResult LoadProtogenFromPath(std::filesystem::path& path, Protogen& protogen)
    {
        // We want to assume we're loading the project file. Make sure it exists and all that. 
        auto filePath = path/PROTOGEN_FILE_NAME;

        std::ifstream ifs(filePath);
        rapidjson::IStreamWrapper isw(ifs);
        
        rapidjson::Document d;
        d.ParseStream(isw);

        if(d.HasParseError())
        {
            const char* msg = rapidjson::GetParseError_En(d.GetParseError());
            auto err = std::format("JSON Error at offset {}: {}\n", d.GetErrorOffset(), msg);
            return { LoadResult::JsonError, err };
        }
        else
        {
            return { LoadResult::Success, "Success" };
            protogen = LoadProtogenFromJSON(d);
        }

    }

    void SaveProtogen(std::filesystem::path& path, Protogen& data)
    {
        rapidjson::Document d;
        d.SetObject();
        SaveProtogenToJSON(data, d.GetObject(), d);
        
        auto filePath = path/PROTOGEN_FILE_NAME;
        std::ofstream ofs(filePath);
        rapidjson::OStreamWrapper osw(ofs);
        
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
        d.Accept(writer);
    }


    //        void LoadIntoGrids(std::filesystem::path& rootPath, const char* fileName, ExpressionDataVector& grids)
    // {
    //     // Load up a bunch of expressions
    //     grids.clear();
    //     for (const auto & entry : std::filesystem::directory_iterator(rootPath))
    //     {
    //         auto directoryPath = entry.path();
    //         auto file = directoryPath/fileName;
    
    //          // Load file and decode image.
    //         std::vector<u8> image;
    //         u32 width, height;
    //         u32 error = lodepng::decode(image, width, height, file.string().c_str());
    
    //         // Expect RGB format
    //         assert(width * height * 4 == image.size());
    //         assert(error == 0);
    
    //         // Load the expression into memory.. As... Greyscale! I guess. 
    //         ExpressionData& expression = grids.emplace_back(width, height);
    //         expression.grid.Fill(0);
    
    //         for(int y = 0; y < height; y++)
    //         {
    //             for(int x = 0; x < width; x++)
    //             {
    //                 int baseIndex = (y * (width * 4) + (x * 4));
    //                 expression.grid.Set(x, y, image[baseIndex]);
    //             }
    //         }
    //     }
    // }
}