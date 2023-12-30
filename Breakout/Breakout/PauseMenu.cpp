#include "ErrorHandler.h"
#include "PauseMenu.h"


PauseMenu* PauseMenu::pause_menu = nullptr;
const char* const PauseMenu::pause_menu_selection_box_text[] = { "Continue", /*"Restart",*/ "Quit", "Exit"};


// TODO [lpavic]: coppied from main menu, see how to improve this
// setup attributes of PauseMenu singleton object, 
// setup graphics for first scene when Main menu is entered
PauseMenu::PauseMenu(SDL_Window* const* const window,
                    const unsigned& window_horizontal_size,
                    const unsigned& window_vertical_size) : Menu()
{
    this->window = *window;
	this->window_horizontal_size = window_horizontal_size;
	this->window_vertical_size = window_vertical_size;

    /////////////////////CHECK IF EVERYTHING IS OK//////////////////
    this->font_size_title = this->window_vertical_size / 5;
    this->font_size_selection_box = this->font_size_title / 2;
    
    this->font_title = TTF_OpenFont(font_path_title, font_size_title);
    if (this->font_title == nullptr)
    {
        THROW_FAILURE((std::string("Error while initializing font title for Pause Menu: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }
    
    this->font_selection_box = TTF_OpenFont(font_path_selection_box, font_size_selection_box);
    if (this->font_selection_box == nullptr)
    {
        THROW_FAILURE((std::string("Error while initializing font selection box for Pause Menu: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }

    // magenta
    this->color_title = {255, 0, 255, 255};
    // white
    this->color_unselected_menu_box = {255, 255, 255, 255};
    // yellow
    this->color_selected_menu_box = {249, 215, 28, 255};

    this->selector = PauseMenu::PAUSE_MENU_SELECTION_BOX::CONTINUE;
    this->selection_box = new SDL_Rect[static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count)];
    
    this->renderer = SDL_CreateRenderer(*window, -1, 0);
    if (this->renderer == nullptr)
    {
        THROW_FAILURE((std::string("Error while initializing renderer for Pause Menu: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
    }

    this->title.h = this->window_vertical_size / 5;
    this->title.w = this->window_horizontal_size / 2;
    this->title.y = 0;
    this->title.x = this->window_horizontal_size / 2 - title.w / 2;

    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = TTF_RenderText_Solid(this->font_title, "P A U S E", this->color_title);
    if (surface == nullptr)
    {
        THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for font title: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        THROW_FAILURE((std::string("Error while initializing texture for Pause Menu for surface for font title: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
    }

    surface->w = title.w;
    surface->h = title.h;

    if (SDL_RenderCopy(renderer, texture, NULL, &title) < 0)
    {
        THROW_FAILURE((std::string("Error while copying texture of font title to renderer in Pause menu: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // TODO [lpavic]: drawing of selectors should be private function (maybe virtual and protected
    // inside Menu class )
    for (unsigned i = 0; i < static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count); i++)
    {
        // dividing by 3 so the selection boxes take only 1/3 of vertical part of the screen
        this->selection_box[i].h = ((this->window_vertical_size / 4) / 
                                    static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count) );
        // each letter of text should take 1/50 of horizontal space of the window
        this->selection_box[i].w = (this->window_horizontal_size / 50) * static_cast<int>(strlen(pause_menu_selection_box_text[i]));
        // TODO [lpavic]: multiplying with this->selection_box[i].h could be problematic if 
            // all selection boxes are not the same height; multiplying i by 2 because of blank space
        this->selection_box[i].y = (this->window_vertical_size / 3) + (i * this->selection_box[i].h);
        this->selection_box[i].x = this->window_horizontal_size / 2 - this->selection_box[i].w / 2;

        SDL_Surface* surface;
        SDL_Texture* texture;

        if (i == static_cast<int>(selector))
        {
            surface = TTF_RenderText_Solid(font_selection_box, 
                                            pause_menu_selection_box_text[i], 
                                            this->color_selected_menu_box);
            if (surface == nullptr)
            {
                THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for seleciton box: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
            }
        }
        else
        {
            surface = TTF_RenderText_Solid(font_selection_box, 
                                            pause_menu_selection_box_text[i], 
                                            this->color_unselected_menu_box);
            if (surface == nullptr)
            {
                THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for seleciton box: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
            }
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            THROW_FAILURE((std::string("Error while initializing texture for Pause Menu for surface for selection box: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
        }

        surface->w = this->selection_box[i].w;
        surface->h = this->selection_box[i].h;

        if (SDL_RenderCopy(renderer, texture, NULL, (selection_box + i)) < 0)
        {
            THROW_FAILURE((std::string("Error while copying texture of selection box to renderer in Pause menu: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
        }

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
    ////////////////////////////////////////////////////////
}


// deallocate all pointers (for SDL pointers, use deallocation functions implemented inside SDL library)
PauseMenu::~PauseMenu()
{
    // TODO [lpavic]: deallocate window pointer, but this pointer should be shared so 
        // game object still has its own pointer
}


PauseMenu* PauseMenu::getInstance(SDL_Window* const * const window,
                                    const unsigned& window_horizontal_size,
                                    const unsigned& window_vertical_size)
{
    if (pause_menu == nullptr)
    {
        pause_menu = new PauseMenu(window, window_horizontal_size, window_vertical_size);
    }
    return pause_menu;
}


void PauseMenu::destroy()
{
    if (this->pause_menu)
    {
        delete this->pause_menu;
        this->pause_menu = nullptr;
    }
}


// TODO [lpavic]: coppied from main menu, see how to improve this
const PauseMenu::PAUSE_MENU_SELECTION_BOX PauseMenu::runImplementation()
{
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return PauseMenu::PAUSE_MENU_SELECTION_BOX::EXIT;
            }
        
            const Uint8* keyboard = SDL_GetKeyboardState(NULL);

            if (keyboard[SDL_SCANCODE_ESCAPE])
			{
                return PauseMenu::PAUSE_MENU_SELECTION_BOX::CONTINUE;
            }
            
            if  (keyboard[SDL_SCANCODE_RETURN])
            {
                switch (this->selector)
                {
                    case PauseMenu::PAUSE_MENU_SELECTION_BOX::CONTINUE:
                        return PauseMenu::PAUSE_MENU_SELECTION_BOX::CONTINUE;
                        break;
                    
                    // case PauseMenu::RESTART:
                    //     return PauseMenu::PAUSE_MENU_SELECTION_BOX::RESTART;
                    //     break;
                    
                    case PauseMenu::PAUSE_MENU_SELECTION_BOX::QUIT:
                        return PauseMenu::PAUSE_MENU_SELECTION_BOX::QUIT;
                        break;
                    
                    case PauseMenu::PAUSE_MENU_SELECTION_BOX::EXIT:
                        return PauseMenu::PAUSE_MENU_SELECTION_BOX::EXIT;
                        break;
                    default:
                        THROW_FAILURE("Unknown state of Main menu!\n");
                }
            }

            if (keyboard[SDL_SCANCODE_DOWN])
            {
                this->selector = static_cast<PauseMenu::PAUSE_MENU_SELECTION_BOX>(
                    (static_cast<int>(this->selector) + 1) 
                    % static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count)
                );

                // TODO [lpavic]: drawing of selectors should be private function (maybe virtual and protected
                // inside Menu class )
                for (unsigned i = 0; i < static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count); i++)
                {
                    SDL_Surface* surface;
                    SDL_Texture* texture;

                    if (i == static_cast<int>(selector))
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        pause_menu_selection_box_text[i], 
                                                        this->color_selected_menu_box);
                        if (surface == nullptr)
                        {
                            THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for seleciton box: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
                        }
                    }
                    else
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        pause_menu_selection_box_text[i], 
                                                        this->color_unselected_menu_box);
                        if (surface == nullptr)
                        {
                            THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for seleciton box: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
                        }
                    }

                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    if (texture == nullptr)
                    {
                        THROW_FAILURE((std::string("Error while initializing texture for Pause Menu for surface for selection box: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
                    }

                    surface->w = this->selection_box[i].w;
                    surface->h = this->selection_box[i].h;

                    if (SDL_RenderCopy(renderer, texture, NULL, (selection_box + i)) < 0)
                    {
                        THROW_FAILURE((std::string("Error while copying texture of selection box to renderer in Pause menu: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
                    }

                    SDL_FreeSurface(surface);
                    SDL_DestroyTexture(texture);
                }
                SDL_RenderPresent(renderer);
                ///////////////////////
            }

            if (keyboard[SDL_SCANCODE_UP])
            {
                if (this->selector == static_cast<PauseMenu::PAUSE_MENU_SELECTION_BOX>(0))
                {
                    this->selector = static_cast<PauseMenu::PAUSE_MENU_SELECTION_BOX>(
                        static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count) - 1
                    );
                }
                else
                {
                    this->selector = static_cast<PauseMenu::PAUSE_MENU_SELECTION_BOX>(
                        static_cast<int>(this->selector) - 1
                    );
                }

                // TODO [lpavic]: drawing of selectors should be private function (maybe virtual and protected
                // inside Menu class )
                for (unsigned i = 0; i < static_cast<int>(PauseMenu::PAUSE_MENU_SELECTION_BOX::Count); i++)
                {
                    SDL_Surface* surface;
                    SDL_Texture* texture;

                    if (i == static_cast<int>(selector))
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        pause_menu_selection_box_text[i], 
                                                        this->color_selected_menu_box);
                        if (surface == nullptr)
                        {
                            THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for seleciton box: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
                        }
                    }
                    else
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        pause_menu_selection_box_text[i], 
                                                        this->color_unselected_menu_box);
                        if (surface == nullptr)
                        {
                            THROW_FAILURE((std::string("Error while initializing surface for Pause Menu for seleciton box: TTF_GetError(): ") + std::string(TTF_GetError()) + std::string("\n")).c_str());
                        }
                    }
                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    if (texture == nullptr)
                    {
                        THROW_FAILURE((std::string("Error while initializing texture for Pause Menu for surface for selection box: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
                    }

                    surface->w = this->selection_box[i].w;
                    surface->h = this->selection_box[i].h;

                    if (SDL_RenderCopy(renderer, texture, NULL, (selection_box + i)) < 0)
                    {
                        THROW_FAILURE((std::string("Error while copying texture of selection box to renderer in Pause menu: SDL_GetError(): ") + std::string(SDL_GetError()) + std::string("\n")).c_str());
                    }

                    SDL_FreeSurface(surface);
                    SDL_DestroyTexture(texture);

                    SDL_RenderPresent(renderer);
                }
                /////////////////////////
            }
        }
    }
}
