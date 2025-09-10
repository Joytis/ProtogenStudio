#pragma once

using u8 = unsigned char;
using u16 = unsigned short;
using s8 = char;
using s32 = int;
using u32 = unsigned int;

namespace Proto
{

    // Colors
    namespace Color
    {
        constexpr tracy::Color::ColorType Root = tracy::Color::PaleGreen;
        constexpr tracy::Color::ColorType Delay = tracy::Color::Gray34;
        constexpr tracy::Color::ColorType GPU = tracy::Color::LavenderBlush1;
        constexpr tracy::Color::ColorType SDL = tracy::Color::LightGoldenrodYellow;
        constexpr tracy::Color::ColorType ExternalImGui = tracy::Color::Orange;
        constexpr tracy::Color::ColorType ProtoImGui = tracy::Color::Teal;
        constexpr tracy::Color::ColorType ProtoProcessing = tracy::Color::Teal;
    }

    struct StackDepth
    {
        enum StackDepthType
        {
            Shallow = 10,
            Middle = 20,
            Deep = 30,
        };
    };
}