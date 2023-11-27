#pragma once

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL_image.h>
#include <SDL_rect.h>
#include <iostream>

// TODO [lpavic]: see to improve implementation
class GameElement
{
// TODO [lpavic]: see that all attributes are used
protected:
    std::string ID{""};
	std::string texture_path{""};
    SDL_Rect texture{0};
    double velocityX{0};
    double velocityY{0};

public:
    GameElement() = default;
    GameElement(const GameElement&) = default;
    GameElement(GameElement&&) = default;
    GameElement& operator =(const GameElement&) = default;
    GameElement& operator =(GameElement&&) = default;
    virtual ~GameElement() = default;

    // TODO [lpavic]: see if this function should be virtual and reimplemented in derived classes
    void drawSprite(SDL_Renderer* const * const renderer);

	const std::string& getID() const;
    const SDL_Rect& getTexture() const;
	const std::string& getTexturePath() const;
    const double& getVelocityX() const;
    const double& getVelocityY() const;
	void setID(const std::string ID);
    void setTexture(const SDL_Rect texture);
    void setVelocityX(const double velocity_x);
    void setVelocityY(const double velocity_y);
};