#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
}

#include "GameElement.h"

#include <iostream>

// TODO [lpavic]: see to improve implementation
class Paddle : public GameElement
{
private:
	std::string hit_sound{""};
public:
    Paddle();
    Paddle(const Paddle&) = default;
    Paddle(Paddle&&) = default;
    Paddle& operator =(const Paddle&) = default;
    Paddle& operator =(Paddle&&) = default;
    virtual ~Paddle() = default;

	// getters and setters
    inline const std::string& getHitSound() const { return this->hit_sound; }
	
    inline void setHitSound(const std::string& hit_sound) { this->hit_sound = hit_sound; }
};
