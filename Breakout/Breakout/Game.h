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
    const STATE runMainMenu();
    const STATE runLevel();

public:
    // constructors and assign operator
    static Game& getInstance();
    Game(const Game&) = delete;
    Game& operator =(const Game&) = delete;

    // public methods
    // this method is implemented as state machine
    void runImplementation();

    // getters and setters
    inline const STATE& getState() const { return this->state; }
	// TODO [lpavic]: there is no const since there would need const_cast for SDL_Window* a = this->getWindow(); invokation - better to use smart pointers in classes
    inline SDL_Window* getWindow() const { return this->window; }
    inline const unsigned& getWindowHorizontalSize() const { return this->window_horizontal_size; }
    inline const unsigned& getWindowVerticalSize() const { return this->window_vertical_size; }

    inline void setState(const STATE& state) { this->state = state; }
	// TODO [lpavic]: use smart pointer
    inline void setWindow(SDL_Window* const window) { this->window = window; }
    inline void setWindowHorizontalSize(const unsigned& window_horizontal_size) { this->window_horizontal_size = window_horizontal_size; }
    inline void setWindowVerticalSize(const unsigned& window_vertical_size) { this->window_vertical_size = window_vertical_size; }
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
