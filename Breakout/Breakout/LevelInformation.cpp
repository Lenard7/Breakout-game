#include "ErrorHandler.h"
#include "LevelInformation.h"
#include "Resources.h"

#include <SDL_ttf.h>

#include <iostream>
LevelInformation::LevelInformation() {}


LevelInformation::LevelInformation(const SDL_Rect& texture, const std::string& font_type, const int font_size, 
                                   const std::string& display_string, const SDL_Color& color)
{
    this->texture = texture;
    this->font = TTF_OpenFont((std::string(Resources::fonts_resources) + font_type).c_str(), font_size);
    if (this->font == nullptr)
    {
        THROW_FAILURE((std::string("Font for Level Information not opened properly: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }
    this->display_string = display_string;
    this->color = color;
}


LevelInformation& LevelInformation::operator =(LevelInformation&& level_information)
{
    if (this != &level_information)
    {
        this->texture = level_information.texture;
        if (this->font)
        {
            TTF_CloseFont(this->font);
        }
        this->font = level_information.font;
        level_information.font = 0;
        this->display_string = level_information.display_string;
        this->color = level_information.color;
    }

    return *this;
}


void LevelInformation:: drawSurface(SDL_Renderer* const * const renderer, const std::string& display_string_value)
{
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = TTF_RenderText_Solid(this->font, (this->display_string + display_string_value).c_str(), this->color);
    if (surface == nullptr)
    {
        THROW_FAILURE((std::string("Surface for rendering Level Information not initialized properly: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }
    
    texture = SDL_CreateTextureFromSurface(*renderer, surface);
    if (texture == nullptr)
    {
        THROW_FAILURE((std::string("Texture for rendering Level Information not initialized properly: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }

    surface->w = this->texture.w;
    surface->h = this->texture.h;

    if (SDL_RenderCopy(*renderer, texture, NULL, &(this->texture)) < 0)
    {
        THROW_FAILURE((std::string("Texture for rendering Level Information not initialized properly: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


LevelInformation::~LevelInformation()
{
    if (this->font)
    {
        TTF_CloseFont(this->font);
    }
}


const SDL_Rect LevelInformation::getTexture() const { return this->texture; }
