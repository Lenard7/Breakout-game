/***********************************************/
#include <cstdio> // TODO [lpavic]: test which libraries are not needed here
#include <cstdlib>
#include <string>
#include <exception>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Level.h"

// Constants for parsing XML file
#define LEVELNUM 1
#define NAMELEVEL "Level"
#define NAMEEXTENSION ".xml"
//#define PATHRESOURCES "" 
//#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
#define PATHRESOURCES "\.\.\\\.\.\\Resources\\" // ..\..\resources\

// Constants for SDL library and graphics implementation
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// TODO [lpavic]: Implement main program here, loading levels, see when is last level...
int main()
{
    for (unsigned int i = 0; i < LEVELNUM; i++)
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError docError;
        errno_t err;
        char* levelFileName;
        size_t fileNameLength;
        char* levelOrdinalNum;

        levelOrdinalNum = (char*) malloc(floor(log10(i + 1) + 2)); // handle warning
        snprintf(levelOrdinalNum, strlen(levelOrdinalNum) + 1, "%d", i + 1);

        fileNameLength = strlen(PATHRESOURCES) + strlen(NAMELEVEL) + strlen(levelOrdinalNum) + strlen(NAMEEXTENSION) + 1;
        levelFileName = (char*)malloc(sizeof(char*) * fileNameLength);
        snprintf(levelFileName, fileNameLength, "%s%s%s%s", PATHRESOURCES, NAMELEVEL, levelOrdinalNum, NAMEEXTENSION);
        // levelFileName = std::string(PATHRESOURCES) + std::string(NAMELEVEL) + std::to_string(i + 1) + ".xml";

        FILE* fp;
        err = fopen_s(&fp, levelFileName, "rb");
        if (err == 0)
        {
            // print message that file is correctly opened
        }
        else
        {
            // print message that file is correctly opened
            return -1;
        }

        try
        {
            std::cout << levelFileName << "\n"; // testing purpose only // TODO [lpavic]: erase later
            docError = doc.LoadFile(fp);
            std::cout << docError << "\n\n"; // testing purpose only // TODO [lpavic]: erase later


            // TODO [lpavic]: implement error handling
            // Getting parsed data from xml into levelObject object
            Level levelObject(doc);



            //TODO [lpavic]: implement Graphics here

            ////////////////////
            
            //delete &levelObject; // TODO [lpavic]: not sure if this is OK
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << "\n";
            return -1;
        }

        // Implementation graphics with SDL library
        SDL_SetMainReady(); // That will do any initialization that is needed by SDL 
                            // (currently does nothing other than setting a global variable named SDL_MainIsReady to true)

        SDL_Window* window = NULL;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        {
            std::cout << "SDL could not be initialized: " <<
                SDL_GetError();
        }
        else 
        {
            std::cout << "SDL video system is ready to go\n";
        }

        window = SDL_CreateWindow("BreakOut.exe",
            100,
            250,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        bool isRunning = true;
        while (isRunning)
        {
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    isRunning = false;
                }
            }
        }


        SDL_DestroyWindow(window);

        SDL_Quit();



    }

    return 0;
}