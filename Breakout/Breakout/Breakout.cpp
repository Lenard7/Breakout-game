#include "Game.h"

extern "C" {
#include <SDL_ttf.h>
} 

#include <iostream>
#include <string>


/** NOTES [lpavic] - follow these rules before merging to main branch:
 * before pushing to git repository, always build in Debug and Release configurations
 * always check if some header, dll or other lib objects are needed somewhere or it is not when making bigger changes
 * edit README.md file after bigger changes
 * refresh BREAKOUT-GAME\Doc\Element_hierarchy.txt when needed
 * beware of const correctnes
 * check for code writing style (where to use Pascal case, snake case, Camel case etc.)
 * check in which order should be attributes and methods be written inside definition of class (alphabetical, data types...)
 * check what is passed to function calls and what they are returning, use reference and pointers for larger data types (custom one, but also for basic one to be consistent, but not for bool or single char which have less memory than their address)
 * check error cases inside code, e.g. if (SDL_Init() < 0) {...}
 * resolve warnings after major implementation
 * see to use rule of 3/5/6
 * see where to improve some implementation inside classes or simillar
 * see where to inline functions
 * see which variables are not used and remove them if they are not used
 * make intendations correct (also free lines at the end of files)
 * take in considerations if some methods should be private, variables protected etc.
 * see which methods need to be marked as noexcept - also check usage of keywords explicit and final
 * see that getters and setters written in C++ way (https://stackoverflow.com/questions/51615363/how-to-write-c-getters-and-setters)
 * make getters and setters for all private and protected attributes for future potentional use
 * let compiler decide if small methods should be inlined by defining methods inside class' definition
 * try to use smart pointer and/or containers instead of raw pointers and also inside each destructor check if all pointers are freed - see which container is appropriate in which situation
 * e.g. std::vector causes unnecessary dynamic memory allocation and sometimes is better to use some other container
 */


/** TODOs outside code (in workspace folder)
 * TODO [lpavic]: There is no resource managament system, resources are loading from the disk "on the fly". For example:
 *      sounds, sprites, fonts -> Release configuration will not handle parsing xml files -> xml files, images, sounds etc.
 *      should be inside "Resource Files" folder
 * TODO [lpavic]: make .xml files to have only brick types that are used inside each level
 */


/** General TODOs inside code
 * TODO [lpavic]: Many constants are hardcoded.
 * TODO [lpavic]: try to use template (functions and classes) where there is needed
 */


/**
 * TODO [lpavic]: display black screen with only certain messages:
    - when new level is entered, message should be: "LEVEL level_ordinal_num", delayed for 2 seconds
    - when game is won, message should be: "WIN!", by pressing key "Esc" Main menu should be displayed
    - when game is lost, message should be: "GAME LOST!", by pressing key "Esc" Main menu should be displayed
 */


int main()
{
    try
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            return -1;
        }

        if (TTF_Init() == -1)
        {
            return -1;
        }
        
        Game & breakout = Game::getInstance();
        breakout.runImplementation();
    }
    catch (std::string e)
    {
        std::cout << e << "\n";

        TTF_Quit();
        SDL_Quit();
        
        return -1;
    }
    
    TTF_Quit();
    SDL_Quit();

    return 0;
}
