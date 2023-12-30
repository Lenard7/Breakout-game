#pragma once

#include <string>


// TODO [lpavic]: consider using std::filesystem::path
namespace Resources
{
    // "..\..\Resources\"
    constexpr char path_resources[] = "..\\..\\Resources\\";
    // "..\..\Resources\Levels\"
    constexpr char level_resources[] = "..\\..\\Resources\\Levels\\";
    // "..\..\Resources\Sounds\"
    constexpr char sound_resources[] = "..\\..\\Resources\\Sounds\\";
    // "..\..\Resources\Textures\"
    constexpr char texture_resources[] = "..\\..\\Resources\\Textures\\";
    // "..\..\Resources\Textures\Fonts\"
    constexpr char fonts_resources[] = "..\\..\\Resources\\Textures\\Fonts\\";
}
