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
    Paddle() noexcept;
    Paddle(const Paddle& paddle) noexcept = default;
    Paddle(Paddle&& paddle) noexcept = default;
    Paddle& operator =(const Paddle& paddle) noexcept = default;
    Paddle& operator =(Paddle&& paddle) noexcept = default;
    virtual ~Paddle() noexcept = default;

	// getters and setters
    inline const std::string& getHitSound() const noexcept { return this->hit_sound; }
	
    inline void setHitSound(const std::string& hit_sound) noexcept { this->hit_sound = hit_sound; }
};
