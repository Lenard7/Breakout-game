#include "Menu.h"


const char Menu::font_path_title[] = "..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF";
const char Menu::font_path_selection_box[] = "..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF";


Menu::~Menu() 
{
    if (this->renderer)
    {
        SDL_RenderClear(this->renderer);
        SDL_RenderPresent(this->renderer);
        SDL_DestroyRenderer(this->renderer);
    }

    if (this->font_title)
    {
        TTF_CloseFont(this->font_title);
    }

    if (this->selection_box)
    {
        delete[] this->selection_box;
    }

    if (this->font_selection_box)
    {
        TTF_CloseFont(this->font_selection_box);
    }
}