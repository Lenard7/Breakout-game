#include "Game.h"

#include <SDL_ttf.h>

#include <iostream>
#include <string>


/**
 * before pushing to git repository, always build in Debug and Release configurations
 * always check if some header, dll or other lib objects are needed somewhere or it is not when making bigger changes
 * edit README.md file
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
 * TODO [lpavic]: after major implementation, resolve warnings
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
    // TODO[lpavic]: see if those SDL_Init and TTF_Init should be inside try block and also see which error messages should be printed out
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return -1;
    }

    if (TTF_Init() == -1)
    {
        return -1;
    }

    try
    {
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


/* Old implementation, see what to use, and what to discard */
#if 0




/***********************************************/
/********************BreakOut*******************/



/*******************************************************************************************************************************/
/********************************************************************** IMPORTANT INCLUDES *********************************************************************/
// this #define is needed because of error when snprintf or strcpy was used: "This function or variable may be unsafe"
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <stdlib.h>

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "Level.h"
#include "HandleGraphics.h"
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/

/*******************************************************************************************************************************/
/*********************************************************GLOBAL VARIABLES**********************************************************************/
/*Global Variables*/
int numOfLives;
unsigned int window_horizontal_size = 0;
unsigned int window_vertical_size = 0;
int ballSpeed = 20;
int paddleSpeed = 20;
int totalScore = 0;
int OFFSET = 0;
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/

/*******************************************************************************************************************************/
/***************************************************ERROR HANDLING****************************************************************************/
#ifndef NDEBUG
// print error with file name and line number in debug mode - file name and line number would be written wrong(always the same value no metter where throw happened) without using macros
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: In file\n\n" + std::string(__FILE__) + "\nat line " + std::to_string((long long)(__LINE__)) + "\n\n" + x)
#else
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: " + std::string(x))
#endif
#define THROW_FAILURE(x) (throw std::string(FILE_AND_LINE_ERR_MSG(x)))
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/


int main(int argc, char** argv)
{

    /*******************************************************************************************************************************/
    /************************************************************CONSTANTS FOR PARSING XML FILES*******************************************************************/
    // Constants for parsing XML file
    constexpr unsigned int LEVELNUM = 3;
    constexpr char NAMELEVEL[] = "Level";
    constexpr char NAMEEXTENSION[] = ".xml";

    // "..\..\Resources\Levels\"
    constexpr char PATHRESOURCES[] = "\.\.\\\.\.\\Resources\\Levels\\";
    // "..\..\Resources\Textures\"
    constexpr char PATHTEXTURES[] = "\.\.\\\.\.\\Resources\\Textures\\";
    // "..\..\Resources\Sounds\"
    constexpr char PATHSOUNDS[] = "\.\.\\\.\.\\Resources\\Sounds\\";
    /*******************************************************************************************************************************/
    /*******************************************************************************************************************************/

Beginning:
    try
    {

        /*******************************************************************************************************************************/
        /******************************************************INITIALIZING GRAPHICHS*************************************************************************/
        // That will do any initialization that is needed by SDL - setting a global variable named SDL_MainIsReady to true
        SDL_SetMainReady();

        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SetupWindowSettings(&window, &renderer);

        TTF_Init();
        
        TTF_Font* font = TTF_OpenFont("..\\..\\Resources\\Textures\\Fonts\\arial.ttf", font_size);
        SDL_Color color = {255, 255, 255};
        /*******************************************************************************************************************************/
        /*******************************************************************************************************************************/


MainMenu:

        /*******************************************************************************************************************************/
        /********************************************************SETTING GAMEOVER AND NUMOFLIVES VARIABLES***********************************************************************/
        bool gameOver = false;

        if (LEVELNUM < 1)
        {
            THROW_FAILURE("Level configuration invalid or corrupted!\n");
            return -1;
        }
        else if (LEVELNUM >= 1 && LEVELNUM < 4)
        {
            numOfLives = LEVELNUM - 1;
        }
        else
        {
            numOfLives = 3;
        }
        /*******************************************************************************************************************************/
        /*******************************************************************************************************************************/


        /*******************************************************************************************************************************/
        /************************************************FOR LOOP ITIRETING THROUGH EACH LEVEL*******************************************************************************/
        for (unsigned int i = 0; i < LEVELNUM; i++)
        {
            /*******************************************************************************************************************************/
            /*********************************************************PARSING XML FILES AND LOADING LEVEL DATA FROM IT**********************************************************************/
            bool levelFinished = false;

            tinyxml2::XMLDocument doc;
            tinyxml2::XMLError docError;
            char* levelFileName;
            size_t fileNameLength;
            char* levelOrdinalNum;

            levelOrdinalNum = (char*) malloc((int)(floor(log10(i + 1) + 2)));
            snprintf(levelOrdinalNum, (int)(floor(log10(i + 1) + 2)), "%u", i + 1);

            fileNameLength = strlen(PATHRESOURCES) + strlen(NAMELEVEL) + strlen(levelOrdinalNum) + strlen(NAMEEXTENSION) + 1;
            levelFileName = (char*)malloc(sizeof(char*) * fileNameLength);
            snprintf(levelFileName, fileNameLength, "%s%s%s%s", PATHRESOURCES, NAMELEVEL, levelOrdinalNum, NAMEEXTENSION);
            
            printf("Loading level:%s\n", levelFileName);
            FILE* fp = fopen(levelFileName, "rb");
            if (fp)
            {
                std::cout << "Configuration file successfully loaded!\n";
            }
            else
            {
                THROW_FAILURE("Cannot open configuration file:\nFile corrupted or file does not exist!\n");
            }

            std::cout << levelFileName << "\n"; // print levelFileName
            docError = doc.LoadFile(fp);

            // Getting parsed data from xml into levelObject object
            Level levelObject(doc);
            /*******************************************************************************************************************************/
            /*******************************************************************************************************************************/



            /*******************************************************************************************************************************/
            /******************************************************VARIABLES FOR RENDERING LEVEL SCENE*************************************************************************/
            //Data for level are parsed and rendering the level starts
            bool shutDown = false;
            SDL_Rect paddle;
            SDL_Rect ball;
            SDL_Rect numOfLivesRect;
            SDL_Rect levelNumRect;
            SDL_Rect scoreRect;
            SDL_Rect brick;
            int lastTime = 0;
            int frameCount = 0;
            int lastFrame;
            int fps;
            double velocityX;
            double velocityY;
            bool *bricks = new bool [levelObject.getRowCount() * levelObject.getColumnCount()];
            /*******************************************************************************************************************************/
            /*******************************************************************************************************************************/


            /*******************************************************************************************************************************/
            /*****************************************************SETTING FIRST MOMENT WHEN LEVEL IS LOADED**************************************************************************/
            setLevelScene(bricks, 
                numOfLivesRect, 
                levelNumRect,
                scoreRect,
                paddle, 
                ball, 
                brick, 
                velocityY, 
                velocityX, 
                levelObject);

            bool isRunning = true;
            bool isPaused = false;
            /*******************************************************************************************************************************/
            /*******************************************************************************************************************************/


            /*******************************************************************************************************************************/
            /**************************************************WHILE GAMEPLAY LASTS - NOT EXITING GAME OR NOT ENTERING MAIN MENU*****************************************************************************/
            while (isRunning)
            {
                /*******************************************************************************************************************************/
                /**********************************************************MINOR STUFF AND CONDITIONS*********************************************************************/
                std::cout << "velocity of ball: X: " << velocityX << " , Y: " << velocityY << "\n";
                RestartFrame(lastFrame,
                    lastTime,
                    fps,
                    frameCount);
                
                if (numOfLives < 1)
                {
                    gameOver = true;
                    goto EndingLevelSequence;
                }
                /*******************************************************************************************************************************/
                /*******************************************************************************************************************************/



                /*******************************************************************************************************************************/
                /***************************************************WHAT HAPPENS WHEN THERE IS INTERSECTION BETWEEN PADDLE AND BALL****************************************************************************/
                if (SDL_HasIntersection(&paddle, &ball))
                {
                    SDL_AudioSpec wavSpec;
                    Uint32 wavLength;
                    Uint8* wavBuffer;
                    
                    std::string tempSoundPath = std::string(PATHSOUNDS) + std::string("activation.wav");
                    if (SDL_LoadWAV(tempSoundPath.c_str(), &wavSpec, &wavBuffer, &wavLength) == NULL)
                    {
                        fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
                    }
                    else
                    {
                        // open audio device
                        SDL_AudioDeviceID deviceId;

                        deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

                        // play audio
                        int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                        SDL_PauseAudioDevice(deviceId, 0);

                        //SDL_CloseAudioDevice(deviceId);
                        SDL_FreeWAV(wavBuffer);
                    }
                    
                    RelativePositionBallPaddle(paddle,
                        ball,
                        velocityX,
                        velocityY);
                }
                /*******************************************************************************************************************************/
                /*******************************************************************************************************************************/


                /*******************************************************************************************************************************/
                /************************************************************SETTING POSITION OF BALL AND PADDLE*******************************************************************/
                SetLimitSituations(paddle,
                    ball,
                    numOfLivesRect,
                    velocityX,
                    velocityY);
                
                ball.x += static_cast<int>(velocityX);
                ball.y += static_cast<int>(velocityY);
                /*******************************************************************************************************************************/
                /*******************************************************************************************************************************/


                /*******************************************************************************************************************************/
                /*****determine the position of  bricks one by one inside for loop, checking if there is intersection between ball and each brick (making sound), checking if the level is over********/
                bool reset = true;

                std::vector<BrickType>& vecRef = levelObject.getPointerToBlockOfBricks();
                
                for (unsigned int j = 0; j < levelObject.getColumnCount() * levelObject.getRowCount(); j++)
                {
                    brick.x = (j % levelObject.getColumnCount()) * (brick.w + levelObject.getColumnSpacing()) + levelObject.getColumnSpacing() / 2;
                    brick.y = numOfLivesRect.h + (j / levelObject.getColumnCount()) * (brick.h + levelObject.getRowSpacing()) + levelObject.getRowSpacing() / 2;
                    if (SDL_HasIntersection(&ball, &brick) && bricks[j])
                    {
                        SDL_AudioSpec wavSpec;
                        Uint32 wavLength;
                        Uint8* wavBuffer;

                        std::string tempSoundPath = std::string(PATHSOUNDS) + std::string("activation.wav");
                        if (SDL_LoadWAV(tempSoundPath.c_str(), &wavSpec, &wavBuffer, &wavLength) == NULL)
                        {
                            fprintf(stderr, "Could not open .wav file: %s\n", SDL_GetError());
                        }
                        else
                        {
                            // open audio device
                            SDL_AudioDeviceID deviceId;
                            
                            deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

                            // play audio
                            int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                            SDL_PauseAudioDevice(deviceId, 0);

                            //SDL_CloseAudioDevice(deviceId);
                            SDL_FreeWAV(wavBuffer);
                        }
                        
                        if (vecRef[j].getID() != "I")
                        {
                            int tempHitPoints = std::stoi(levelObject.getBlockOfBricks()[j].getHitPoints());
                            tempHitPoints--;
                            std::string tempHitPointsString = std::to_string(tempHitPoints);
                            vecRef[j].setHitPoints(tempHitPointsString);

                            if (std::stoi(levelObject.getBlockOfBricks()[j].getHitPoints()) <= 0)
                            {
                                bricks[j] = false;
                                totalScore += levelObject.getBlockOfBricks()[j].getBreakScore();
                            }
                        }

                        RelativePositionBallBrick(ball,
                            brick,
                            velocityX,
                            velocityY);
                    }
                    if (bricks[j] && vecRef[j].getID() != "I")
                    {
                        reset = false;
                    }
                }
                if (reset)
                {
                    levelFinished = true;
                    goto EndingLevelSequence;
                }
                /*******************************************************************************************************************************/
                /*******************************************************************************************************************************/


                /**************************************************Handling Pausing and Exiting game*****************************************************************************/
                /*******************************************************************************************************************************/


                /***************reseting isPaused variable if it was true from before****************/
                /************************************************************************************/
                if (isPaused)
                {
                    isPaused = false;
                }
                /************************************************************************************/
                /************************************************************************************/

                /************************Checking if game needs to be shut down**********************/
                /************************************************************************************/

                // https://stackoverflow.com/questions/29373203/sdl-2-0-key-repeat-and-delay
                // reading from keyboard should not be inside 
                // while (SDL_PollEvent) loop because of
                // first delay when pressing one button for longer
                // time
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {                    
                    shutDown = ReadInput(isRunning,
                        isPaused,
                        event,
                        paddle,
                        velocityX,
                        velocityY);

                    if (shutDown) 
                    { 
                        goto EndingLevelSequence; 
                    }
                }

                /************************************************************************************/
                /************************************************************************************/


                /****************************************Pause sequence******************************/
                /************************************************************************************/

                while (isPaused)
                {
                    SDL_Event pauseMenuEvent;
                    
                    while (SDL_PollEvent(&pauseMenuEvent))
                    {
                        shutDown = ReadInputForPausedMenu(isRunning,
                            isPaused,
                            pauseMenuEvent);

                    }

                    if (shutDown)
                    {
                        goto EndingLevelSequence;
                    }

                    if (!isPaused)
                    {
                        break;
                    }
                    
                }

                /************************************************************************************/
                /************************************************************************************/
                /************************************************************************************/
                /************************************************************************************/


                /*************************************Rendering the level***********************************************/
                /************************************************************************************/


                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                RefreshFrames(frameCount,
                    lastFrame);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &paddle);
                SDL_RenderFillRect(renderer, &ball);
                
                std::string tempPath = std::string(PATHTEXTURES) + std::string("Paddle.png");
                DrawSprite(&renderer,
                    paddle,
                    tempPath);
                tempPath = std::string(PATHTEXTURES) + std::string("Ball.png");
                DrawSprite(&renderer,
                    ball,
                    tempPath);

                /********************Write lives remaining, levelNum and score***********/
                std::string tempNumOfLivesDisplay = "Lives:" + std::to_string(numOfLives);
                const char* numOfLivesDisplay = tempNumOfLivesDisplay.c_str();
                DrawSurface(numOfLivesRect,
                    &renderer,
                    numOfLivesDisplay,
                    &font,
                    color);
                std::string tempLevelString = "Level:" + std::to_string(i + 1);
                const char* levelString = tempLevelString.c_str();
                DrawSurface(levelNumRect,
                    &renderer,
                    levelString,
                    &font,
                    color);
                std::string tempTotalScoreString = "Score:" + std::to_string(totalScore);
                const char* totalScoreString = tempTotalScoreString.c_str();
                DrawSurface(scoreRect,
                    &renderer,
                    totalScoreString,
                    &font,
                    color);
                
                /********Drawing bricks**********/
                for (unsigned int j = 0; j < levelObject.getColumnCount() * levelObject.getRowCount(); j++)
                {
                    if (bricks[j]) 
                    {
                        tempPath = std::string(PATHTEXTURES);
                        switch (levelObject.getBlockOfBricks()[j].getID()[0])
                        {
                            case 'S':
                                tempPath += std::string("Soft.png");
                                break;
                            case 'M':
                                tempPath += std::string("Medium.png");
                                break;
                            case 'H':
                                tempPath += std::string("Hard.png");
                                break;
                            case 'I':
                                tempPath += std::string("Impenetrable.png");
                                break;
                            default:
                                break;
                        }

                        brick.x = (j % levelObject.getColumnCount()) * (brick.w + levelObject.getColumnSpacing()) + levelObject.getColumnSpacing() / 2;
                        brick.y = numOfLivesRect.h + (j / levelObject.getColumnCount()) * (brick.h + levelObject.getRowSpacing()) + levelObject.getRowSpacing() / 2;
                        SDL_RenderFillRect(renderer, &brick);
                        DrawSprite(&renderer,
                            brick,
                            tempPath);
                    }
                }
                SDL_RenderPresent(renderer);   
            }
                /************************************************************************************/
                /************************************************************************************/
            /************************************************************************************/
            /************************************************************************************/


        EndingLevelSequence:
            free(levelOrdinalNum);
            if (shutDown) 
            {
                goto ShutDownSequence; 
            }

            if (gameOver) 
            { 
                totalScore = 0;
                goto MainMenu; 
            }
        }

ShutDownSequence:
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    catch (std::string e)
    {
        std::cout << e << "\n";
        return -1;
    }
   
    return 0;
}

#endif