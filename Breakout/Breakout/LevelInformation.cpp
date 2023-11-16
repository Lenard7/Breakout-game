#include "LevelInformation.h"
#include "Resources.h"

#include <SDL_ttf.h>

#include <iostream>
LevelInformation::LevelInformation() {}


LevelInformation::LevelInformation(const SDL_Rect& texture, const std::string& font_type, const int font_size, 
                                   const std::string& display_string, const SDL_Color& color)
{
    std::cout << TTF_Init() << std::endl;
    this->texture = texture;
    std::cout << std::endl << (std::string(Resources::fonts_resources) + font_type).c_str();
    // this->font = TTF_OpenFont((std::string(Resources::fonts_resources) + font_type).c_str(), font_size);
    this->font = TTF_OpenFont("..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF", font_size);
    std::cout << "font" << font <<std::endl;
    std::cout << "TTF_GetError: " << TTF_GetError() << std::endl;
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

    TTF_Init();
    // surface = TTF_RenderText_Solid(*font, displayString, color);
    std::cout << "TTF_GetError: " << TTF_GetError() << std::endl;
    // surface = TTF_RenderText_Solid(this->font, (this->display_string + display_string_value).c_str(), this->color);
    surface = TTF_RenderText_Solid(this->font, "Something", this->color);
    std::cout << "TTF_GetError: " << TTF_GetError() << std::endl;
    
    texture = SDL_CreateTextureFromSurface(*renderer, surface);

    // surface->w = surfaceRect.w;
    // surface->h = surfaceRect.h;
    surface->w = this->texture.w;
    surface->h = this->texture.h;

    // SDL_RenderCopy(*renderer, texture, NULL, &surfaceRect);
    SDL_RenderCopy(*renderer, texture, NULL, &(this->texture));

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


LevelInformation::~LevelInformation()
{
    if (this->font)
    {
        TTF_CloseFont(this->font);
    }

    TTF_Quit();
}


const SDL_Rect LevelInformation::getTexture() const { return this->texture; }
