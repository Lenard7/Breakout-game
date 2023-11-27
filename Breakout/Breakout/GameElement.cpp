# include "GameElement.h"


void GameElement::drawSprite(SDL_Renderer* const * const renderer)
{
    SDL_Surface* surface;
    SDL_Texture* sdl_texture;

    surface = IMG_Load(this->texture_path.c_str());
    sdl_texture = SDL_CreateTextureFromSurface(*renderer, surface);

    surface->w = this->texture.w;
    surface->h = this->texture.h;

    SDL_RenderCopy(*renderer, sdl_texture, NULL, &this->texture);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(sdl_texture);
}


const std::string& GameElement::getID() const { return this->ID; }
const SDL_Rect& GameElement::getTexture() const { return this->texture; }
const std::string& GameElement::getTexturePath() const { return this->texture_path; }
const double& GameElement::getVelocityX() const { return this->velocityX; }
const double& GameElement::getVelocityY() const { return this->velocityY; }
void GameElement::setID(const std::string ID) { this->ID = ID; }
void GameElement::setTexture(const SDL_Rect texture) { this->texture = texture;}
void GameElement::setVelocityX(const double velocity_x) { this->velocityX = velocity_x; }
void GameElement::setVelocityY(const double velocity_y) { this->velocityY = velocity_y; }
