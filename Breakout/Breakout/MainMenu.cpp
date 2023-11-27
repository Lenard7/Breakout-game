#include "MainMenu.h"

#include "ErrorHandler.h"


MainMenu* MainMenu::main_menu = nullptr;
const char* const MainMenu::main_menu_selection_box_text[] = { "New game", "Exit"};


MainMenu* MainMenu::getInstance(SDL_Window** window,
                                    unsigned& window_horizontal_size,
                                    unsigned& window_vertical_size)
{
    if (main_menu == nullptr)
    {
        main_menu = new MainMenu(window, window_horizontal_size, window_vertical_size);
    }
    return main_menu;
}


// setup attributes of MainMenu singleton object, 
// setup graphics for first scene when Main menu is entered
MainMenu::MainMenu(SDL_Window** window,
                    unsigned& window_horizontal_size,
                    unsigned& window_vertical_size) : Menu()
{
    this->window = *window;
	this->window_horizontal_size = window_horizontal_size;
	this->window_vertical_size = window_vertical_size;

    this->font_size_title = this->window_vertical_size / 5;
    this->font_size_selection_box = this->font_size_title / 2;
    this->font_title = TTF_OpenFont(font_path_title, font_size_title);
    this->font_selection_box = TTF_OpenFont(font_path_selection_box, font_size_selection_box);

    // magenta
    this->color_title = {255, 0, 255, 255};
    // white
    this->color_unselected_menu_box = {255, 255, 255, 255};
    // yellow
    this->color_selected_menu_box = {249, 215, 28, 255};

    this->selector = MainMenu::MAIN_MENU_SELECTION_BOX::NEW_GAME;
    this->selection_box = new SDL_Rect[MainMenu::MAIN_MENU_SELECTION_BOX::Count];
    this->renderer = SDL_CreateRenderer(*window, -1, 0);


    title.h = this->window_vertical_size / 5;
    title.w = this->window_horizontal_size / 2;
    title.y = 0;
    title.x = this->window_horizontal_size / 2 - title.w / 2;

    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = TTF_RenderText_Solid(this->font_title, "B R E A K O U T", this->color_title);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    surface->w = title.w;
    surface->h = title.h;

    SDL_RenderCopy(renderer, texture, NULL, &title);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // TODO [lpavic]: drawing of selectors should be private function (maybe virtual and protected
    // inside Menu class )
    for (unsigned i = 0; i < MainMenu::MAIN_MENU_SELECTION_BOX::Count; i++)
    {
        // dividing by 3 so the selection boxes take only 1/3 of vertical part of the screen
        this->selection_box[i].h = ((this->window_vertical_size / 4) / 
                                    static_cast<int>(MainMenu::MAIN_MENU_SELECTION_BOX::Count) );
        // each letter of text should take 1/50 of horizontal space of the window
        this->selection_box[i].w = (this->window_horizontal_size / 50) * static_cast<int>(strlen(main_menu_selection_box_text[i]));
        // TODO [lpavic]: multiplying with this->selection_box[i].h could be problematic if 
            // all selection boxes are not the same height; multiplying i by 2 because of blank space
        this->selection_box[i].y = (this->window_vertical_size / 3) + (i * this->selection_box[i].h);
        this->selection_box[i].x = this->window_horizontal_size / 2 - this->selection_box[i].w / 2;

        SDL_Surface* surface;
        SDL_Texture* texture;

        if (i == static_cast<int>(selector))
        {
            surface = TTF_RenderText_Solid(font_selection_box, 
                                            main_menu_selection_box_text[i], 
                                            this->color_selected_menu_box);
        }
        else
        {
            surface = TTF_RenderText_Solid(font_selection_box, 
                                            main_menu_selection_box_text[i], 
                                            this->color_unselected_menu_box);
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        surface->w = this->selection_box[i].w;
        surface->h = this->selection_box[i].h;

        SDL_RenderCopy(renderer, texture, NULL, (selection_box + i));

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}


// deallocate all pointers (for SDL pointers, use deallocation functions implemented inside SDL library)
MainMenu::~MainMenu()
{
    // TODO [lpavic]: deallocate window pointer, but this pointer should be shared so 
        // game object still has its own pointer
}


void MainMenu::destroy()
{
    if (this->main_menu)
    {
        delete this->main_menu;
        this->main_menu = nullptr;
    }
}


MainMenu::MAIN_MENU_SELECTION_BOX MainMenu::runImplementation()
{
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return MainMenu::MAIN_MENU_SELECTION_BOX::EXIT;
            }
        
            const Uint8* keyboard = SDL_GetKeyboardState(NULL);

            if  (keyboard[SDL_SCANCODE_RETURN])
            {
                switch (this->selector)
                {
                    case MainMenu::NEW_GAME:
                        return MainMenu::MAIN_MENU_SELECTION_BOX::NEW_GAME;
                        break;
                    case MainMenu::EXIT:
                        return MainMenu::MAIN_MENU_SELECTION_BOX::EXIT;
                        break;
                    default:
                        THROW_FAILURE("Unknown state of Main menu!\n");
                }
            }

            if (keyboard[SDL_SCANCODE_DOWN])
            {
                

                this->selector = static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(
                    (this->selector + static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(1)) 
                    % MainMenu::MAIN_MENU_SELECTION_BOX::Count
                );

                // TODO [lpavic]: drawing of selectors should be private function (maybe virtual and protected
                // inside Menu class )
                for (unsigned i = 0; i < MainMenu::MAIN_MENU_SELECTION_BOX::Count; i++)
                {
                    SDL_Surface* surface;
                    SDL_Texture* texture;

                    if (i == static_cast<int>(selector))
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        main_menu_selection_box_text[i], 
                                                        this->color_selected_menu_box);
                    }
                    else
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        main_menu_selection_box_text[i], 
                                                        this->color_unselected_menu_box);
                    }
                    texture = SDL_CreateTextureFromSurface(renderer, surface);

                    surface->w = this->selection_box[i].w;
                    surface->h = this->selection_box[i].h;

                    SDL_RenderCopy(renderer, texture, NULL, (selection_box + i));

                    SDL_FreeSurface(surface);
                    SDL_DestroyTexture(texture);
                }
                SDL_RenderPresent(renderer);
                ///////////////////////
            }

            if (keyboard[SDL_SCANCODE_UP])
            {
                if (this->selector == static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(0))
                {
                    this->selector = static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(
                        MainMenu::MAIN_MENU_SELECTION_BOX::Count - static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(1)
                    );
                }
                else
                {
                    this->selector = static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(
                        this->selector - static_cast<MainMenu::MAIN_MENU_SELECTION_BOX>(1)
                    );
                }

                // TODO [lpavic]: drawing of selectors should be private function (maybe virtual and protected
                // inside Menu class )
                for (unsigned i = 0; i < MainMenu::MAIN_MENU_SELECTION_BOX::Count; i++)
                {
                    SDL_Surface* surface;
                    SDL_Texture* texture;

                    if (i == static_cast<int>(selector))
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        main_menu_selection_box_text[i], 
                                                        this->color_selected_menu_box);
                    }
                    else
                    {
                        surface = TTF_RenderText_Solid(font_title, 
                                                        main_menu_selection_box_text[i], 
                                                        this->color_unselected_menu_box);
                    }
                    texture = SDL_CreateTextureFromSurface(renderer, surface);

                    surface->w = this->selection_box[i].w;
                    surface->h = this->selection_box[i].h;

                    SDL_RenderCopy(renderer, texture, NULL, (selection_box + i));

                    SDL_FreeSurface(surface);
                    SDL_DestroyTexture(texture);

                    SDL_RenderPresent(renderer);
                }
                /////////////////////////
            }
        }
    }
    
}