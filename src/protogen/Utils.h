#pragma once

namespace Proto
{
    enum class LoadResultType
    {
        Success,
        JsonError,
        FileDoesNotExist,
    };

    struct LoadResult
    {
        LoadResultType result;
        std::string message;
    };
}

namespace Proto::Utils
{
    template <typename TData>
    LoadResult LoadFromJSON(std::filesystem::path& path, TData& data)
    {
        std::ifstream ifs(path);
        rapidjson::IStreamWrapper isw(ifs);
        
        rapidjson::Document d;
        d.ParseStream(isw);
    
        if(d.HasParseError())
        {
            const char* msg = rapidjson::GetParseError_En(d.GetParseError());
            auto err = std::format("JSON Error at offset {}: {}\n", d.GetErrorOffset(), msg);
            return { LoadResultType::JsonError, err };
        }
        else
        {
            data = TData::LoadFromJSON(d);
            return { LoadResultType::Success, "Success" };
        }
    }

    template <typename TData>
    void SaveToJSON(std::filesystem::path& path, TData& data)
    {
        rapidjson::Document d;
        d.SetObject();
        TData::SaveToJSON(data, d.GetObject(), d);
        
        std::ofstream ofs(path);
        rapidjson::OStreamWrapper osw(ofs);
        
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
        d.Accept(writer);
    }
}   