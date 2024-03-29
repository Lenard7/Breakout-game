#pragma once

extern "C" {
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
}

#include <memory>


// In one moment, there can be Main Menu and Options Menu in the same time, so Menu shouldn't be singleton, but there is no need to have copy and move constructors and assign operators
// TODO [lpavic]: see if this class needs to be implemented as abstract class or normal base class for Pause and Main menu;
    // with PauseMenu and MainMenu, there can also be OptionMenu, LoadMenu...
// TODO [lpavic]: see if Factory pattern should be used (maybe it does not, maybe it will only complicate whole design)
class Menu
{
protected:
	static void customDeleterSDLRenderer(SDL_Renderer* renderer);
	// TODO [lpavic]: getter and setter for static member?
    // values of window variable and its dimensions are passed through constructor
    std::shared_ptr<SDL_Window> window{nullptr};
    unsigned window_horizontal_size{0};
    unsigned window_vertical_size{0};

    std::unique_ptr<SDL_Renderer, decltype(&customDeleterSDLRenderer)> renderer{nullptr, &customDeleterSDLRenderer};

    // title
    SDL_Rect title{0};
    // TODO [lpavic]: this font_title maybe should be unique pointer!?
    TTF_Font* font_title{nullptr};
    static const char font_path_title[];
    unsigned font_size_title{0};
    SDL_Color color_title{0, 0, 0, 255};

    // array of selection boxes
    // TODO [lpavic]: this selection_box maybe should be unique pointer!?
    SDL_Rect* selection_box{nullptr};
    // TODO [lpavic]: this font_selection_box maybe should be unique pointer!?
    TTF_Font* font_selection_box{nullptr};
    static const char font_path_selection_box[];
    unsigned font_size_selection_box{0};
    SDL_Color color_unselected_menu_box{0, 0, 0, 255};
    SDL_Color color_selected_menu_box{0, 0, 0, 255};
    
    // TODO [lpavic]: unused variable
    SDL_Rect background_image{0, 0, 0, 0};

public:
    Menu() noexcept = default;
    Menu(const Menu& menu) = delete;
    Menu(Menu&& menu) = delete;
    Menu& operator =(const Menu& menu) = delete;
    Menu& operator =(Menu&& menu) = delete;
    virtual ~Menu();

    // getters and setters
    inline const std::shared_ptr<SDL_Window>& getWindow() const noexcept { return this->window; }
    inline const unsigned& getWindowHorizontalSize() const noexcept { return this->window_horizontal_size; }
    inline const unsigned& getWindowVerticalSize() const noexcept { return this->window_vertical_size; }
	
    inline const std::unique_ptr<SDL_Renderer, decltype(&customDeleterSDLRenderer)>& getRenderer() const noexcept { return this->renderer; }

    inline const SDL_Rect& getTitle() const noexcept { return this->title; }
    inline TTF_Font* getFontTitle() const noexcept { return this->font_title; }
    inline const unsigned& getFontSizeTitle() const noexcept { return this->font_size_title; }
    inline const SDL_Color& getColorTitle() const noexcept { return this->color_title; }

    inline SDL_Rect* getSelectionBox() const noexcept { return this->selection_box; }
    inline TTF_Font* getFontSelectionBox() const noexcept { return this->font_selection_box; }
    inline const unsigned& getFontSizeSelectionBox() const noexcept { return this->font_size_selection_box; }
    inline const SDL_Color& getColorUnselectedMenuBox() const noexcept { return this->color_unselected_menu_box; }
    inline const SDL_Color& getColorSelectedMenuBox() const noexcept { return this->color_selected_menu_box; }

    inline const SDL_Rect& getBackgroundImage() const noexcept { return this->background_image; }
    
    
    inline void setWindow(const std::shared_ptr<SDL_Window>& window) { this->window = window; }
    inline void setWindowHorizontalSize(const unsigned& window_horizontal_size) noexcept { this->window_horizontal_size = window_horizontal_size; }
    inline void setWindowVerticalSize(const unsigned& window_vertical_size) noexcept { this->window_vertical_size = window_vertical_size; }
    inline void setRenderer(std::unique_ptr<SDL_Renderer, decltype(&customDeleterSDLRenderer)>&& renderer ) noexcept { this->renderer = std::move(renderer); }

    inline void setTitle(const SDL_Rect& title) noexcept { this->title = title; }
	// TODO [lpavic]: use smart pointer
    inline void setFontTitle(TTF_Font* const font_title) noexcept { this->font_title = font_title; }
    inline void setFontSizeTitle(const unsigned& font_size_title) noexcept { this->font_size_title = font_size_title; }
    inline void setColorTitle(const SDL_Color& color_title) noexcept { this->color_title = color_title; }

	// TODO [lpavic]: use smart pointer
    inline void setSelectionBox(SDL_Rect* const selection_box) noexcept { this->selection_box = selection_box; }
	// TODO [lpavic]: use smart pointer
    inline void setFontSelectionBox(TTF_Font* const font_selection_box) noexcept { this->font_selection_box = font_selection_box; }
    inline void setFontSizeSelectionBox(const unsigned& font_size_selection_box) noexcept { this->font_size_selection_box = font_size_selection_box; }
    inline void setColorUnselectedMenuBox(const SDL_Color& color_unselected_menu_box) noexcept { this->color_unselected_menu_box = color_unselected_menu_box; }
    inline void setColorSelectedMenuBox(const SDL_Color& color_selected_menu_box) noexcept { this->color_selected_menu_box = color_selected_menu_box; }

    inline void setBackgroundImage(const SDL_Rect& background_image) noexcept { this->background_image = background_image; }
};
