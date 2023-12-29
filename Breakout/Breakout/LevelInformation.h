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
	// TODO [lpavic]: use smart pointer
    TTF_Font* font{nullptr};
    std::string display_string{""};
    SDL_Color color{0, 0, 0, 255};

public:
    LevelInformation(const SDL_Rect& texture, const std::string& font_type, const int& font_size, 
                     const std::string& display_string, const SDL_Color& color);
    LevelInformation() noexcept;
    LevelInformation(const LevelInformation& level_information);
    LevelInformation(LevelInformation&& level_information);
    LevelInformation& operator =(const LevelInformation& level_information);
    LevelInformation& operator =(LevelInformation&& level_information);
    virtual ~LevelInformation();

    void drawSurface(SDL_Renderer* const * const renderer, const std::string& display_string_value);

    //getters and setters
    inline const SDL_Rect& getTexture() const noexcept { return this->texture; }
	// TODO [lpavic]: use smart pointer
    inline TTF_Font* getFont() const noexcept { return this->font; }
    inline const std::string& getDisplayString() const noexcept { return this->display_string; }
    inline const SDL_Color& getColor() const noexcept { return this->color; }

    inline void setTexture(const SDL_Rect& texture) noexcept { this->texture = texture; }
	// TODO [lpavic]: use smart pointer
    inline void setFont(TTF_Font* const font) noexcept { this->font = font; }
    inline void setDisplayString(const std::string& display_string) noexcept { this->display_string = display_string; }
    inline void setColor(const SDL_Color& color) noexcept { this->color = color; }
};
