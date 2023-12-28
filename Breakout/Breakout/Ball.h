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
    Ball();
    Ball(const Ball& ball) = default;
    Ball(Ball&& ball) = default;
    Ball& operator =(const Ball& ball) = default;
    Ball& operator =(Ball&& ball) = default;
    virtual ~Ball() = default;
};
