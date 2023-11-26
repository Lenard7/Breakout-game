#include "Game.h"

#include <SDL_ttf.h>

#include <iostream>
#include <string>


/** NOTES [lpavic]:
 * before pushing to git repository, always build in Debug and Release configurations
 * always check if some header, dll or other lib objects are needed somewhere or it is not when making bigger changes
 * edit README.md file after bigger changes
 * beware of cont correctnes
 * check for code writing style (where to use Pascal case, snake case, Camel case etc.)
 * check in which order should be attributes and methods be written inside definition of class (alphabetical, data types...)
 * check what is passed to function calls
 * check error cases inside code, e.g. if (SDL_Init() < 0) {...}
 * resolve warnings after major implementation
 */


/** TODOs outside code (in workspace folder)
 * TODO [lpavic]: There is no resource managament system, resources are loading from the disk "on the fly". For example:
 *      sounds, sprites, fonts -> Release configuration will not handle parsing xml files -> xml files, images, sounds etc.
 *      should be inside "Resource Files" folder
 * TODO [lpavic]: make .xml files to have only brick types that are used inside each level
 * TODO [lpavic]: write inheritance classes inside BREAKOUT-GAME\Doc\Element_hierarchy.txt
 */


/** General TODOs inside code
 * TODO [lpavic]: Many constants are hardcoded.
 * TODO [lpavic]: Functions take and return data by value in cases when it is not efficient. E.g. coping std::string, 
    std::vector causes unnecessary dynamic memory allocation.
 * TODO [lpavic]: try to use template (functions and classes) where there is needed
 */


/**
 * TODO [lpavic]: display black screen with only certain messages:
    - when new level is entered, message should be: "LEVEL levelOrdinalNum", delayed for 2 seconds
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
