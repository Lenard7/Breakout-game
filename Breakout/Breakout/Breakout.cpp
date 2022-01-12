/***********************************************/
/********************BreakOut*******************/

#include <cstdio> // TODO [lpavic]: test which libraries are not needed here
#include <cstdlib>
#include <string>
#include <exception>
//#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include "Level.h"
#include "HandleGraphics.h"

// Constants for parsing XML file
#define LEVELNUM 3 // TODO [lpavic]: variable LEVELNUM should be dynamic variable depending on number of "Level" files
#define NAMELEVEL "Level"
#define NAMEEXTENSION ".xml"
#define PATHRESOURCES "\.\.\\\.\.\\Resources\\" // ..\..\Resources\

#define PATHTEXTURES "\.\.\\\.\.\\Textures\\" // ..\..\Textures\

#define PATHSOUNDS "\.\.\\\.\.\\Sounds\\" // ..\..\Sounds\


/*Global Variables*/
int numOfLives;
unsigned int SCREEN_horizontal = 0;
unsigned int SCREEN_vertical = 0;
int ballSpeed = 20;
int paddleSpeed = 20;
int totalScore = 0;
int OFFSET = 0;

// TODO [lpavic]: implement error handling
/*
#ifdef DEBUG
// print error with File name, Line number and custom message
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: In file\n\n" + std::string(__FILE__) + "\nat line " + std::to_string((long long)(__LINE__)) + "\n\n" + x)
#else
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: " + std::string(x))
#endif

#define THROW_FAILURE(x) (throw std::iostream::failure(FILE_AND_LINE_ERR_MSG(x)))
*/

// TODO [lpavic]: handle bug when ball stucks between Impenetrable brick and upper screen grid
int main()
{
Beginning:
    bool gameOver = false;
    
    // TODO [lpavic]: implement function that will check levelnum variable
    if (LEVELNUM < 1)
    {
        std::cout << "Level configuration invalid or corrupted!\n";
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

    for (unsigned int i = 0; i < LEVELNUM; i++)
    {
        bool levelFinished = false;

        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError docError;
        errno_t err;
        char* levelFileName;
        size_t fileNameLength;
        char* levelOrdinalNum;

        levelOrdinalNum = (char*) malloc(static_cast<size_t>(floor(log10(i + 1) + 2)));
        snprintf(levelOrdinalNum, strlen(levelOrdinalNum) + 1, "%d", i + 1);

        fileNameLength = strlen(PATHRESOURCES) + strlen(NAMELEVEL) + strlen(levelOrdinalNum) + strlen(NAMEEXTENSION) + 1;
        levelFileName = (char*)malloc(sizeof(char*) * fileNameLength);
        snprintf(levelFileName, fileNameLength, "%s%s%s%s", PATHRESOURCES, NAMELEVEL, levelOrdinalNum, NAMEEXTENSION);
        
        FILE* fp;
        err = fopen_s(&fp, levelFileName, "rb");
        if (err == 0)
        {
            std::cout << "Configuration file successfully loaded!\n";
        }
        else
        {
            std::cout << "Cannot open configuration file:\n"
                << "File corrupted or file does not exist!\n";
            return -1;
        }

        try
        {
            std::cout << levelFileName << "\n"; // print levelFileName
            docError = doc.LoadFile(fp);
            std::cout << docError << "\n\n"; // print docError

            // Getting parsed data from xml into levelObject object
            Level levelObject(doc);
        
            // Implementation graphics with SDL library

            // TODO [lpavic]: move SDL_Init and SetupWindowSettings before main for loop, at the beginning of main function
                // so window wont load when level is loaded

            SDL_SetMainReady(); // That will do any initialization that is needed by SDL 
                                // setting a global variable named SDL_MainIsReady to true

            // TODO [lpavic]: see where to put all these definitions
            bool shutDown = false;
            SDL_Window* window = NULL;
            SDL_Renderer* renderer = NULL;
            
            // TODO [lpavic]: maybe some variables should be put inside new class
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
            
            SetupWindowSettings(&window, &renderer);
            TTF_Init();
            
            TTF_Font* font = TTF_OpenFont("Fonts\\arial.ttf", FONT_SIZE); // TODO [lpavic]: move Fonts folder outside work folder
            SDL_Color color = { 255, 255, 255 };

            /*
                // TODO [lpavic]: make delay of 3 seconds; on window should be written "LEVEL %d"
            */

            setLevelScene(&bricks, 
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
            while (isRunning)
            {
                std::cout << "velocity of ball: X: " << velocityX << " , Y: " << velocityY << "\n";
                RestartFrame(lastFrame,
                    lastTime,
                    fps,
                    frameCount);

                if (numOfLives < 1)
                {
                    gameOver = true;
                    goto Close;
                }
                if (SDL_HasIntersection(&paddle, &ball))
                {
                    // TODO [lpavic]: make this loading a sound as a function
                    SDL_AudioSpec wavSpec;
                    Uint32 wavLength;
                    Uint8* wavBuffer;

                    std::string tempSoundPath = std::string(PATHSOUNDS) + std::string("activation.wav");
                    if (SDL_LoadWAV(tempSoundPath.c_str(), &wavSpec, &wavBuffer, &wavLength) == NULL) // TODO [lpavic]: load relative path to .wav file
                    {
                        fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
                    }
                    else
                    {
                        // open audio device
                        SDL_AudioDeviceID deviceId;
                        deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0); // TODO [lpavic]: after some time, it returns error, i.e 0

                        // play audio
                        int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                        SDL_PauseAudioDevice(deviceId, 0);

                        SDL_FreeWAV(wavBuffer);
                    }

                    RelativePositionBallPaddle(paddle,
                        ball,
                        velocityX,
                        velocityY);
                }
                SetLimitSituations(paddle,
                    ball,
                    numOfLivesRect,
                    velocityX,
                    velocityY);
                
                ball.x += static_cast<int>(velocityX);
                ball.y += static_cast<int>(velocityY);

                bool reset = true;

                std::vector<BrickType>& vecRef = levelObject.getPointerToBlockOfBricks();
                
                for (unsigned int j = 0; j < levelObject.getColumnCount() * levelObject.getRowCount(); j++)
                {
                    brick.x = (j % levelObject.getColumnCount()) * (brick.w + levelObject.getColumnSpacing()) + levelObject.getColumnSpacing() / 2; // TODO [lpavic]: is it here neccessary, in drawing this function runs again
                    brick.y = numOfLivesRect.h + (j / levelObject.getColumnCount()) * (brick.h + levelObject.getRowSpacing()) + levelObject.getRowSpacing() / 2; // TODO [lpavic]: is it here neccessary, in drawing this function runs again
                    if (SDL_HasIntersection(&ball, &brick) && bricks[j])
                    {
                        // TODO [lpavic]: make this loading sound as a function
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
                            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

                            // play audio
                            int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                            SDL_PauseAudioDevice(deviceId, 0);

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
                    goto Close;
                }

                /***************INPUT***************/
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {                    
                    shutDown = ReadInput(isRunning,
                        event,
                        paddle,
                        velocityX,
                        velocityY);
                    if (shutDown) { goto Close; }
                }

                /***************RENDER***************/
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
                std::string tempNumOfLivesDisplay = "Lives:" + std::to_string(numOfLives); // TODO [lpavic]: display as multiline string
                const char* numOfLivesDisplay = tempNumOfLivesDisplay.c_str();
                DrawSurface(numOfLivesRect,
                    &renderer,
                    numOfLivesDisplay,
                    &font,
                    color);
                std::string tempLevelString = "Level:" + std::to_string(i + 1); // TODO [lpavic]: display as multiline string
                const char* levelString = tempLevelString.c_str();
                DrawSurface(levelNumRect,
                    &renderer,
                    levelString,
                    &font,
                    color);
                std::string tempTotalScoreString = "Score:" + std::to_string(totalScore); // TODO [lpavic]: display as multiline string
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
                            default:    // TODO [lpavic]: maybe do something useful in this case
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
Close:
            TTF_CloseFont(font);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            if (shutDown) { goto Exit; }
            if (gameOver) 
            { 
                totalScore = 0;
                goto Beginning; 
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << "\n";
            return -1;
        }
 
    }
Exit:
    return 0;
}