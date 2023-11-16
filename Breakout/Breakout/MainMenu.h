#pragma once

#include "Menu.h"


// this class is made as singleton

class MainMenu : public Menu
{
public:
    enum MAIN_MENU_SELECTION_BOX
    {
        NEW_GAME = 0,
        EXIT,
        Count // this member is for count of enum elements
    };

private:
    static MainMenu * main_menu;
    MAIN_MENU_SELECTION_BOX selector;
    static const char* const main_menu_selection_box_text[];

    MainMenu(SDL_Window** window, unsigned& window_horizontal_size, unsigned& window_vertical_size);
    virtual ~MainMenu();

public:
    static MainMenu * getInstance(SDL_Window** window, 
                                unsigned& window_horizontal_size,
                                unsigned& window_vertical_size);
    MainMenu(const MainMenu &) = delete;
    MainMenu & operator = (const MainMenu &) = delete;
    void destroy();

    // this method is implemented as state machine
    MAIN_MENU_SELECTION_BOX runImplementation();
};
