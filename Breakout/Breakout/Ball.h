#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
}

#include "GameElement.h"

#include <iostream>

class Ball : public GameElement
{
public:
    Ball() noexcept;
    Ball(const Ball& ball) noexcept = default;
    Ball(Ball&& ball) noexcept = default;
    Ball& operator =(const Ball& ball) noexcept = default;
    Ball& operator =(Ball&& ball) noexcept = default;
    virtual ~Ball() noexcept = default;
};
