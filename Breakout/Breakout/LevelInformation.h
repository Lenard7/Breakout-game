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
    LevelInformation(const SDL_Rect& texture, const std::string& font_type, const int& font_size, 
                     const std::string& display_string, const SDL_Color& color);
    LevelInformation(const LevelInformation&) = default;
    LevelInformation(LevelInformation&&) = default;
    LevelInformation& operator =(const LevelInformation&) = default;
    LevelInformation& operator =(LevelInformation&& level_information);
    virtual ~LevelInformation();

    void drawSurface(SDL_Renderer* const * const renderer, const std::string& display_string_value);

    //getters and setters
    inline const SDL_Rect& getTexture() const { return this->texture; }
	// TODO [lpavic]: use smart pointer
    inline TTF_Font* getFont() const { return this->font; }
    inline const std::string& getDisplayString() const { return this->display_string; }
    inline const SDL_Color& getColor() const { return this->color; }

    inline void setTexture(const SDL_Rect& texture) { this->texture = texture; }
    inline void setFont(TTF_Font* const font) { this->font = font; }
    inline void setDisplayString(const std::string& display_string) { this->display_string = display_string; }
    inline void setColor(const SDL_Color& color) { this->color = color; }
};
