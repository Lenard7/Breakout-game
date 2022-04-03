#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "Level.h"
#include <SDL_ttf.h>

// TODO [lpavic]: make FONT_SIZE as variable which value depends on characteristics of user's screen properties
#define FONT_SIZE 96

extern int paddleSpeed;
extern int ballSpeed;
extern int numOfLives;
extern unsigned int SCREEN_horizontal;
extern unsigned int SCREEN_vertical;
extern int OFFSET;

void GetDesktopResolution(unsigned int& horizontal, 
    unsigned int& vertical);
void SetupWindowSettings(SDL_Window** window, 
    SDL_Renderer** renderer);
void setLevelScene(bool** bricks,
    SDL_Rect& numOfLivesRect,
    SDL_Rect& levelNumRect,
    SDL_Rect& scoreRect,
    SDL_Rect& paddle,
    SDL_Rect& ball,
    SDL_Rect& brick,
    double& velocityY,
    double& velocityX,
    Level& levelObject);
void RestartFrame(int& lastFrame,
    int& lastTime,
    int& fps,
    int& frameCount);
void RelativePositionBallPaddle(SDL_Rect& paddle,
    SDL_Rect& ball,
    double& velocityX,
    double& velocityY);
void SetLimitSituations(SDL_Rect& paddle,
    SDL_Rect& ball,
    SDL_Rect& numOfLivesRect,
    double& velocityX,
    double& velocityY);
void RelativePositionBallBrick(SDL_Rect& ball,
    SDL_Rect& brick,
    double& velocityX,
    double& velocityY);
bool ReadInput(bool& isRunning,
    bool& isPaused,
    SDL_Event& event,
    SDL_Rect& paddle,
    double& velocityX,
    double& velocityY);
void RefreshFrames(int& frameCount,
    int& lastFrame);
void DrawSurface(SDL_Rect& surfaceRect,
    SDL_Renderer** renderer,
    const char* displayString,
    TTF_Font** font,
    SDL_Color& color);
void DrawSprite(SDL_Renderer** renderer,
    SDL_Rect& paddle,
    std::string tempPath);
bool ReadInputForPausedMenu(bool& isRunning,
    bool& isPaused,
    SDL_Event& pauseMenuEvent);