#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL_image.h>
#include <SDL_rect.h>
}

#include <iostream>


class GameElement
{
// TODO [lpavic]: see that all attributes are used
protected:
    std::string ID{""};
    SDL_Rect texture{0};
	std::string texture_path{""};
    double velocity_x{0};
    double velocity_y{0};

public:
    GameElement() = default;
    GameElement(const GameElement& game_element) = default;
    GameElement(GameElement&& game_element) = default;
    GameElement& operator =(const GameElement& game_element) = default;
    GameElement& operator =(GameElement&& game_element) = default;
    virtual ~GameElement() = default;

    // TODO [lpavic]: see if this function should be virtual and reimplemented in derived classes
    void drawSprite(SDL_Renderer* const * const renderer);

    // getters and setters
	inline const std::string& getID() const { return this->ID; }
    inline const SDL_Rect& getTexture() const { return this->texture; }
	inline const std::string& getTexturePath() const { return this->texture_path; }
    inline const double& getVelocityX() const { return this->velocity_x; }
    inline const double& getVelocityY() const { return this->velocity_y; }

    inline void setID(const std::string& ID) { this->ID = ID; }
    inline void setTexture(const SDL_Rect& texture) { this->texture = texture; }
    inline void setTexturePath(const std::string& texture_path) { this->texture_path = texture_path; }
    inline void setVelocityX(const double& velocity_x) { this->velocity_x = velocity_x; }
    inline void setVelocityY(const double& velocity_y) { this->velocity_y = velocity_y; }
};
