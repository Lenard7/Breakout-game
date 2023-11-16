#include "Ball.h"
#include "Resources.h"


// TODO [lpavic]: see if this initialization of texture_path can go in header file with {}
Ball::Ball() : GameElement() 
{
    this->texture_path = std::string(Resources::texture_resources) + std::string("Ball.png"); 
}