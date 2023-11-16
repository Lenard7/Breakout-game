#pragma once

/* Old implementation, see what to use, and what to discard */
#if 0

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif
#include <SDL.h>
#include <SDL_image.h>
#include "Level.h"
#include <SDL_ttf.h>

// TODO [lpavic]: make font_size as variable which value depends on characteristics of user's screen properties
#define font_size 96

extern int paddleSpeed;
extern int ballSpeed;
extern int numOfLives;
extern unsigned int window_horizontal_size;
extern unsigned int window_vertical_size;
extern int OFFSET;

void GetDesktopResolution(unsigned int& horizontal, 
    unsigned int& vertical);
void SetupWindowSettings(SDL_Window** const window, 
    SDL_Renderer** const renderer);
void setLevelScene(bool*& bricks,
    SDL_Rect& numOfLivesRect,
    SDL_Rect& levelNumRect,
    SDL_Rect& scoreRect,
    SDL_Rect& paddle,
    SDL_Rect& ball,
    SDL_Rect& brick,
    double& velocityY,
    double& velocityX,
    const Level& levelObject);
void RestartFrame(int& lastFrame,
    int& lastTime,
    int& fps,
    int& frameCount);
void RelativePositionBallPaddle(const SDL_Rect& paddle,
    const SDL_Rect& ball,
    double& velocityX,
    double& velocityY);
void SetLimitSituations(SDL_Rect& paddle,
    SDL_Rect& ball,
    const SDL_Rect& numOfLivesRect,
    double& velocityX,
    double& velocityY);
void RelativePositionBallBrick(const SDL_Rect& ball,
    const SDL_Rect& brick,
    double& velocityX,
    double& velocityY);
bool ReadInput(bool& isRunning,
    bool& isPaused,
    const SDL_Event& event,
    SDL_Rect& paddle,
    double& velocityX,
    double& velocityY);
void RefreshFrames(int& frameCount,
    const int& lastFrame);
void DrawSurface(const SDL_Rect& surfaceRect,
    SDL_Renderer* const * const renderer,
    const char* const displayString,
    TTF_Font* const * const font,
    const SDL_Color& color);
void DrawSprite(SDL_Renderer* const * const renderer,
    const SDL_Rect& paddle,
    const std::string tempPath);
bool ReadInputForPausedMenu(bool& isRunning,
    bool& isPaused,
    const SDL_Event& pauseMenuEvent);

#endif