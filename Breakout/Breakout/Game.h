#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL.h>
#include <SDL_image.h>

#include "wtypes.h"
}

// TODO [lpavic]: see to improve implementation
// this class is made as singleton (Meyer's implementation, no need of explicit destructor call)
class Game
{
public:
    // game state
    enum STATE
    {
        MAIN_MENU = 0,
        PLAY,
        END
    };

private:
    // attributes
    STATE state{MAIN_MENU};
    
    SDL_Window* window{nullptr};
    unsigned window_horizontal_size{0};
    unsigned window_vertical_size{0};
    
    // constructor and destructor are private for singleton purpose
    Game();
    ~Game();

    // private methods
    void getDesktopResolution();
    void setupWindowSettings();
    STATE runMainMenu();
    STATE runLevel();

public:
    // constructors and assign operator
    static Game & getInstance();
    Game(const Game&) = delete;
    Game& operator =(const Game&) = delete;

    // public methods
    // this method is implemented as state machine
    void runImplementation();

    // setters and getters
    inline const STATE getState() const { return state; }

    inline void setState(const STATE state) { this->state = state; }
};


/* Meyer's singleton pattern implementation*/
// struct singleton_t
// {

//   static singleton_t &instance()
//   {
//     static singleton_t s;
//     return s;
//   } // instance

//   singleton_t(const singleton_t &) = delete;
//   singleton_t & operator = (const singleton_t &) = delete;

// private:

//   singleton_t() {}
//   ~singleton_t() {}

// };
