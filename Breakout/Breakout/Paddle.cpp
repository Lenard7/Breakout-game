#include "Paddle.h"
#include "Resources.h"


Paddle::Paddle() noexcept(noexcept(GameElement())): GameElement() 
{
    this->texture_path = std::string(Resources::texture_resources) + std::string("Paddle.png");
}
