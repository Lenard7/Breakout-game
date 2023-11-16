#pragma once

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


// TODO [lpavic]: see if this class needs to be implemented as abstract class or normal base class for Pause and Main menu;
    // with PauseMenu and MainMenu, there can also be OptionMenu, LoadMenu...
// TODO [lpavic]: see if Factory pattern should be used (maybe it does not, maybe it will only complicate whole design)
// TODO [lpavic]: see where to use rule of 0/3/5 and where smart pointers can be used
class Menu
{
protected:
    // TODO [lpavic]: this window maybe should be shared pointer!?
    // values of window variable and its dimensions are passed through constructor
    SDL_Window* window{nullptr};
    unsigned window_horizontal_size{0};
    unsigned window_vertical_size{0};

    SDL_Renderer* renderer{nullptr};

    // title
    SDL_Rect title{0};
    TTF_Font* font_title{nullptr};
    static const char font_path_title[];
    unsigned font_size_title{0};
    SDL_Color color_title{0, 0, 0};

    // array of selection boxes
    SDL_Rect* selection_box{nullptr};
    TTF_Font* font_selection_box{nullptr};
    static const char font_path_selection_box[];
    unsigned font_size_selection_box{0};
    SDL_Color color_unselected_menu_box{0, 0, 0};
    SDL_Color color_selected_menu_box{0, 0, 0};
    
    // TODO [lpavic]: unused variable
    SDL_Rect background_image{0, 0, 0, 0};

public:
    Menu() {}
    Menu(const Menu&) = delete;
    Menu& operator =(const Menu&) = delete;
    virtual ~Menu();
};
