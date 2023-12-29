#include "Ball.h"
#include "Resources.h"


Ball::Ball() noexcept(noexcept(GameElement())) : GameElement() 
{
    this->texture_path = std::string(Resources::texture_resources) + std::string("Ball.png"); 
}