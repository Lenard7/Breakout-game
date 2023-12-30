#include "Game.h"
#include "ErrorHandler.h"

#include "Level.h"
#include "MainMenu.h"


Game::Game()
{
    // when entering the game, main window of the game should be opened
    SDL_SetMainReady();
    setupWindowSettings();
}


// in Meyer's singleton implementation, destructor is not called until application terminates
Game::~Game()
{
    if (window)
    {
        // TODO [lpavic]: call custom deleter?
        SDL_DestroyWindow(window);
    }
}


void Game::getDesktopResolution()
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    this->window_horizontal_size = desktop.right;
    this->window_vertical_size = desktop.bottom;
}


void Game::setupWindowSettings()
{
    getDesktopResolution();
    
    this->window_vertical_size = static_cast<unsigned>(/* 0.95 * */ this->window_vertical_size);
    this->window = SDL_CreateWindow("Breakout.exe", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    window_horizontal_size, 
                                    window_vertical_size, 
                                    SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        THROW_FAILURE((std::string("Failed creting SDL window: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
    }
}


const Game::STATE Game::runMainMenu()
{
    MainMenu* main_menu = MainMenu::getInstance(&window, 
                                                window_horizontal_size, 
                                                window_vertical_size);

    while(1)
    {
        switch(main_menu->runImplementation())
        {
            case MainMenu::MAIN_MENU_SELECTION_BOX::NEW_GAME:
                main_menu->destroy();
                return Game::STATE::PLAY;
                break;
            
            case MainMenu::MAIN_MENU_SELECTION_BOX::EXIT:
                main_menu->destroy();
                return Game::STATE::END;
                break;
            
            case MainMenu::MAIN_MENU_SELECTION_BOX::Count:
                THROW_FAILURE("Count state for main menu not valid!\n");
                break;
            
            default:
                THROW_FAILURE("Main menu is in no state!\n");
        }
    }
}


const Game::STATE Game::runLevel()
{
    while(1)
    {
        Level* level = Level::getInstance(&window, 
                                        window_horizontal_size, 
                                        window_vertical_size);

        switch(level->runImplementation())
        {
            case Level::STATE::QUIT:
                level->destroy();
                return Game::STATE::MAIN_MENU;
                break;
            
            case Level::STATE::EXIT:
                level->destroy();
                return Game::STATE::END;
                break;
            
            case Level::STATE::RUNNING:
                THROW_FAILURE("Running is not permited returned state of Level!\n");
                break;

            case Level::STATE::PAUSED:
                THROW_FAILURE("Paused is not permited returned state of Level!\n");
                break;

            // case Level::RESTART:
            //     // TODO [lpavic]: see what to do here, maybe this case shouldnt be here at all
            //     // delete level;
            //     break;
            
            case Level::STATE::Count:
                THROW_FAILURE("Count state for level is not valid!\n");
                break;

            default:
                THROW_FAILURE("Unknown state of Level!\n");
        }
    }
}


Game& Game::getInstance()
{
    static Game game;
    return game;
}


Game::Game(Game&& game)
{
    // TODO [lpavic]: implement this and consider defining smart pointers and also marking as noexcept(warning C26439)
}


Game& Game::operator =(Game&& game)
{
    // TODO [lpavic]: implement this and consider defining smart pointers and also marking as noexcept(warning C26439)
    if (this != &game)
    {

	}

    return *this;
}


void Game::runImplementation()
{
    while (this->getState() != Game::STATE::END)
    {
        switch (this->getState())
        {
            case Game::STATE::MAIN_MENU:
                this->setState(this->runMainMenu());
                break;

            case Game::STATE::PLAY:
                this->setState(this->runLevel());
                break;

            case Game::STATE::END:
                if (window)
                {
                    SDL_DestroyWindow(window);
                }
                
                break;

            default:
                THROW_FAILURE("Unknown game state!\n");
        }
    }
}
