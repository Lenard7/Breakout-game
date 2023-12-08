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
    Ball(const Ball&) = default;
    Ball(Ball&&) = default;
    Ball& operator =(const Ball&) = default;
    Ball& operator =(Ball&&) = default;
    virtual ~Ball() = default;
};
