#pragma once

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>


#include <fstream>

namespace Proto::Utils
{
    template <typename TData>
    void LoadFromJson(std::filesystem::path& path, TData& data)
    {
        std::ifstream ifs(path);
        rapidjson::IStreamWrapper isw(ifs);
        
        rapidjson::Document d;
        d.ParseStream(isw);

        data.Load(d);
    }

    template <typename TData>
    void SaveToJson(std::filesystem::path& path, TData& data)
    {
        rapidjson::Document d;
        d.SetObject();
        data.Save(d);
        
        std::ofstream ofs(path);
        rapidjson::OStreamWrapper osw(ofs);
        
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
        d.Accept(writer);
    }
}   