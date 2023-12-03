#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
}

#include <string>


// TODO [lpavic]: see to improve implementation - also see if this class should be descendant of GameElement class
class LevelInformation
{
private:
    SDL_Rect texture{0, 0, 0, 0};
    TTF_Font* font{nullptr};
    std::string display_string{""};
    SDL_Color color{0, 0, 0, 255};

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
