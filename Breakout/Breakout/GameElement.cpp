# include "ErrorHandler.h"
# include "GameElement.h"

extern "C" {
#include <SDL_ttf.h>
}


void GameElement::drawSprite(SDL_Renderer* const * const renderer)
{
    SDL_Surface* surface;
    SDL_Texture* sdl_texture;

    surface = IMG_Load(this->texture_path.c_str());
    if (surface == nullptr)
    {
        THROW_FAILURE((std::string("Surface for rendering sprite not initialized properly: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }

    sdl_texture = SDL_CreateTextureFromSurface(*renderer, surface);
    if (sdl_texture == nullptr)
    {
        THROW_FAILURE((std::string("Texture for rendering sprite not initialized properly: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }

    surface->w = this->texture.w;
    surface->h = this->texture.h;

    if (SDL_RenderCopy(*renderer, sdl_texture, NULL, &this->texture) < 0)
    {
        THROW_FAILURE((std::string("Texture for rendering sprite not initialized properly: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(sdl_texture);
}


const std::string& GameElement::getID() const { return this->ID; }
const SDL_Rect& GameElement::getTexture() const { return this->texture; }
const std::string& GameElement::getTexturePath() const { return this->texture_path; }
const double& GameElement::getVelocityX() const { return this->velocity_x; }
const double& GameElement::getVelocityY() const { return this->velocity_y; }
void GameElement::setID(const std::string ID) { this->ID = ID; }
void GameElement::setTexture(const SDL_Rect texture) { this->texture = texture;}
void GameElement::setVelocityX(const double velocity_x) { this->velocity_x = velocity_x; }
void GameElement::setVelocityY(const double velocity_y) { this->velocity_y = velocity_y; }
