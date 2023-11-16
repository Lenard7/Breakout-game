#pragma once

#include "Menu.h"


// this class is made as singleton
class PauseMenu : public Menu
{
public:
    enum PAUSE_MENU_SELECTION_BOX
    {
        CONTINUE = 0,
        // RESTART,
        QUIT,
        EXIT,
        Count // this member is for count of enum elements
    };

private:
    static PauseMenu* pause_menu;
    PAUSE_MENU_SELECTION_BOX selector;
    static const char* const pause_menu_selection_box_text[];

    PauseMenu(SDL_Window** window, unsigned& window_horizontal_size, unsigned& window_vertical_size);
    virtual ~PauseMenu();

public:
    static PauseMenu* getInstance(SDL_Window** window, 
                                unsigned& window_horizontal_size,
                                unsigned& window_vertical_size);
    PauseMenu(const PauseMenu &) = delete;
    PauseMenu & operator = (const PauseMenu &) = delete;
    void destroy();

    // this method is implemented as state machine
    PAUSE_MENU_SELECTION_BOX runImplementation();
};
