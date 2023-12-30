#include "Menu.h"


const char Menu::font_path_title[] = "..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF";
const char Menu::font_path_selection_box[] = "..\\..\\Resources\\Textures\\Fonts\\LHANDW.TTF";


Menu::Menu() noexcept
{

}


Menu::Menu(const Menu& menu)
{
    // TODO [lpavic]: implement this and consider defining smart pointers
}


Menu::Menu(Menu&& menu)
{
    // TODO [lpavic]: implement this and consider defining smart pointers and also marking as noexcept(warning C26439)
}


Menu& Menu::operator =(const Menu& menu)
{
    // TODO [lpavic]: implement this and consider defining smart pointers
    // TODO [lpavic]: implement this and consider defining smart pointers
	if (this != &menu)
    {

	}

    return *this;
}


Menu& Menu::operator =(Menu&& menu)
{
    // TODO [lpavic]: implement this and consider defining smart pointers and also marking as noexcept(warning C26439)
	if (this != &menu)
    {

	}

    return *this;
}


Menu::~Menu() 
{
    // TODO [lpavic]: call custom deleter?
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