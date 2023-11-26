#pragma once

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include <string>


// TODO [lpavic]: make intendations correct (also free lines at the end of files)
// TODO [lpavic]: see to improve implementation
// TODO [lpavic]: apply "rule of five" in definition of LevelInformation class
class LevelInformation
{
private:
    SDL_Rect texture{0, 0, 0, 0};
    TTF_Font* font{nullptr};
    std::string display_string{""};
    SDL_Color color{0, 0, 0};

public:
    LevelInformation();
    LevelInformation(const SDL_Rect& texture, const std::string& font_type, const int font_size, 
                     const std::string& display_string, const SDL_Color& color);
    LevelInformation(const LevelInformation&) = default;
    LevelInformation(LevelInformation&&) = default;
    LevelInformation& operator =(const LevelInformation&) = default;
    LevelInformation& operator =(LevelInformation&& level_information);
    virtual ~LevelInformation();

    void drawSurface(SDL_Renderer* const * const renderer, const std::string& display_string_value);

    const SDL_Rect getTexture() const;
};
