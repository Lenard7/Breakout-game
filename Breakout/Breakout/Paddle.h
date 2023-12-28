#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
}

#include "GameElement.h"

#include <iostream>


class Paddle : public GameElement
{
private:
	std::string hit_sound{""};
public:
    Paddle();
    Paddle(const Paddle& paddle) = default;
    Paddle(Paddle&& paddle) = default;
    Paddle& operator =(const Paddle& paddle) = default;
    Paddle& operator =(Paddle&& paddle) = default;
    virtual ~Paddle() = default;

	// getters and setters
    inline const std::string& getHitSound() const { return this->hit_sound; }
	
    inline void setHitSound(const std::string& hit_sound) { this->hit_sound = hit_sound; }
};
