/** TODOs outside code (in workspace folder)
 * TODO [lpavic]: There is no resource managament system, resources are loading from the disk "on the fly". For example:
 *      sounds, sprites, fonts -> Release configuration will not handle parsing xml files -> xml files, images, sounds etc.
 *      should be inside "Resource Files" folder
 * TODO [lpavic]: make .xml files to have only brick types that are used inside each level 
 */

/***********************************************/
/********************BreakOut*******************/
// before pushing to git repository, always build in Debug and Release configurations
// always check if some header, dll or other lib objects are needed somewhere or it is not when making bigger changes
// edit README.md file 

// this #define is needed because of error when snprintf or strcpy was used: "This function or variable may be unsafe"
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <stdlib.h>

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "Level.h"
#include "HandleGraphics.h"


/*Global Variables*/
int numOfLives;
unsigned int SCREEN_horizontal = 0;
unsigned int SCREEN_vertical = 0;
int ballSpeed = 20;
int paddleSpeed = 20;
int totalScore = 0;
int OFFSET = 0;

#ifndef NDEBUG
// print error with file name and line number in debug mode - file name and line number would be written wrong(always the same value no metter where throw happened) without using macros
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: In file\n\n" + std::string(__FILE__) + "\nat line " + std::to_string((long long)(__LINE__)) + "\n\n" + x)
#else
#define FILE_AND_LINE_ERR_MSG(x) ("ERROR: " + std::string(x))
#endif
#define THROW_FAILURE(x) (throw std::string(FILE_AND_LINE_ERR_MSG(x)))


/*General TODOs inside code
* TODO [lpavic]: The game is not implemented using object-oriented principles. On the paper should be drawn
    UML (Unified Modeling Language) diagram
* TODO [lpavic]: Many constants are hardcoded.
* TODO [lpavic]: Functions take and return data by value in cases when it is not efficient. E.g. coping std::string, 
    std::vector causes unnecessary dynamic memory allocation.
* TODO [lpavic]: handle bug when ball stucks between Impenetrable brick and upper screen grid
*/


// TODO [lpavic]: make Game class as a singleton and inside main Game object will call its main methods, like init, startMenu, startgame etc.
int main(int argc, char** argv)
{
    // Constants for parsing XML file
    constexpr unsigned int LEVELNUM = 3; // TODO [lpavic]: variable LEVELNUM should be dynamic variable depending on number of "Level" files - implement searching through file explorer and see how many files are there
    constexpr char NAMELEVEL[] = "Level";
    constexpr char NAMEEXTENSION[] = ".xml";

    // TODO [lpavic]: this paths may not be hardcoded like this, maybe they should be inside resource managament
    // "..\..\Resources\Levels\"
    constexpr char PATHRESOURCES[] = "\.\.\\\.\.\\Resources\\Levels\\";
    // "..\..\Resources\Textures\"
    constexpr char PATHTEXTURES[] = "\.\.\\\.\.\\Resources\\Textures\\";
    // "..\..\Resources\Sounds\"
    constexpr char PATHSOUNDS[] = "\.\.\\\.\.\\Resources\\Sounds\\";
    
Beginning:
    try
    {
        // That will do any initialization that is needed by SDL - setting a global variable named SDL_MainIsReady to true
        SDL_SetMainReady();

        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SetupWindowSettings(&window, &renderer);

        TTF_Init();
        
        TTF_Font* font = TTF_OpenFont("..\\..\\Resources\\Textures\\Fonts\\arial.ttf", FONT_SIZE);
        SDL_Color color = {255, 255, 255};

MainMenu:
        bool gameOver = false;

        /*
        * TODO [lpavic]: make main menu: it should be triggered:
            - at the opening of the game
            - during the game, when "Esc" button is pressed and game is paused
            - when player loses the game
            - when player wins the game
        * TODO [lpavic]: display black screen with only certain messages:
            - when new level is entered, message should be: "LEVEL levelOrdinalNum", delayed for 2 seconds
            - when game is won, message should be: "WIN!", by pressing key "Esc" Main menu should be displayed
            - when game is lost, message should be: "GAME LOST!", by pressing key "Esc" Main menu should be displayed
        */

        // TODO [lpavic]: implement function that will check levelnum variable
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

        for (unsigned int i = 0; i < LEVELNUM; i++)
        {
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
        
            //Data for level are parsed and rendering the level starts
            // TODO [lpavic]: maybe some variables should be put inside new class (declare variables just above where they are really used)
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
                    goto EndingLevelSequence;
                }
                
                if (SDL_HasIntersection(&paddle, &ball))
                {
                    // TODO [lpavic]: make this loading a sound as a function (implement function for loading audio files)
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

                        // TODO [lpavic]: after some time, SDL_OpenAudioDevice returns error, i.e 0
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
                SetLimitSituations(paddle,
                    ball,
                    numOfLivesRect,
                    velocityX,
                    velocityY);
                
                ball.x += static_cast<int>(velocityX);
                ball.y += static_cast<int>(velocityY);

                bool reset = true;

                std::vector<BrickType>& vecRef = levelObject.getPointerToBlockOfBricks();
                
                // TODO [lpavic]: whole game lags when there are more bricks -> optimize drawing bricks and setting bricks (optimize those for loops used)
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
                            SDL_AudioDeviceID deviceId;
                            
                            // TODO [lpavic]: after some time, SDL_OpenAudioDevice returns error, i.e 0
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

                /***************INPUT****************/
                if (isPaused)
                {
                    isPaused = false;
                }

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

                // SEQUENCE: GAME IS PAUSED
                // TODO [lpavic]: implement unpause menu
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
                /***************INPUT****************/
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
                // TODO [lpavic]: display lives, score and level as multiline string
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