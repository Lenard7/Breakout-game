#include "Menu.h"


void Menu::customDeleterSDLRenderer(SDL_Renderer* renderer)
{
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}
}


const char Menu::font_path_title[] = "..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF";
const char Menu::font_path_selection_box[] = "..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF";


Menu::~Menu() 
{
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
