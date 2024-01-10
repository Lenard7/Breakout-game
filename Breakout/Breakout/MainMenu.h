#pragma once

#include "Menu.h"


// this class is made as singleton
class MainMenu : public Menu
{
public:
    enum class MAIN_MENU_SELECTION_BOX
    {
        NEW_GAME = 0,
        EXIT,
        Count // this member is for count of enum elements
    };

private:
    static MainMenu* main_menu;
    MAIN_MENU_SELECTION_BOX selector{MAIN_MENU_SELECTION_BOX::NEW_GAME};
    static const char* const main_menu_selection_box_text[];

    MainMenu(std::shared_ptr<SDL_Window>& window,
                const unsigned& window_horizontal_size,
                const unsigned& window_vertical_size);
    virtual ~MainMenu() = default;

public:
    static MainMenu* getInstance(std::shared_ptr<SDL_Window>& window, 
                                const unsigned& window_horizontal_size,
                                const unsigned& window_vertical_size);
    MainMenu(const MainMenu& main_menu) = delete;
    MainMenu(MainMenu&& main_menu) noexcept = delete;
    MainMenu& operator =(const MainMenu& main_menu) = delete;
    MainMenu& operator =(MainMenu&& main_menu) noexcept = delete;

    void destroy();

    // this method is implemented as state machine
    const MAIN_MENU_SELECTION_BOX runImplementation();

    //getters and setters
    inline const MAIN_MENU_SELECTION_BOX& getSelector() const noexcept { return this->selector; }

    inline void setSelector(const MAIN_MENU_SELECTION_BOX& selector) noexcept { this->selector = selector; }
};
