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
    PAUSE_MENU_SELECTION_BOX selector{CONTINUE};
    static const char* const pause_menu_selection_box_text[];

    PauseMenu(SDL_Window* const * const window, const unsigned& window_horizontal_size, const unsigned& window_vertical_size);
    virtual ~PauseMenu();

public:
    static PauseMenu* getInstance(SDL_Window* const * const window, 
                                const unsigned& window_horizontal_size,
                                const unsigned& window_vertical_size);
    PauseMenu(const PauseMenu& pause_menu) = delete;
    PauseMenu(PauseMenu&& pause_menu) noexcept = default; // this move copy constructor will call move copy constructor of Menu class
    PauseMenu& operator = (const PauseMenu& pause_menu) = delete;
    PauseMenu& operator =(PauseMenu&& pause_menu) noexcept = default;
    
    void destroy();

    // this method is implemented as state machine
    const PAUSE_MENU_SELECTION_BOX runImplementation();

    // getters and setters
    inline const PAUSE_MENU_SELECTION_BOX& getSelector() const noexcept { return this->selector; }

    inline void setSelector(const PAUSE_MENU_SELECTION_BOX& selector) noexcept { this->selector = selector; }
};
