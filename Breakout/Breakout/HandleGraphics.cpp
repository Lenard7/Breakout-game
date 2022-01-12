#include <iostream>
#include <string>
#include <cstdlib>

#include "HandleGraphics.h"
#include "wtypes.h"


void GetDesktopResolution(unsigned int& horizontal, unsigned int& vertical)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;
}


void SetupWindowSettings(SDL_Window** window, 
    SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialized: Error "
            << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialized successfully!\n";
    }

    GetDesktopResolution(SCREEN_horizontal, SCREEN_vertical);
    SCREEN_vertical = static_cast<int>(0.95 * SCREEN_vertical); // hardcoded so title track can be seen; see for better dynamicall solution
    OFFSET = static_cast<int>(min(SCREEN_vertical, SCREEN_horizontal) * 0.01); // 1% of min dimenzion of screen
                                                             // TODO [lpavic]: this variable is implemented because some
                                                             // functions have delay, like SDL_HasIntersection();

    if (SDL_CreateWindowAndRenderer(SCREEN_horizontal,
        SCREEN_vertical,
        0,
        window,
        renderer) < 0)
    {
        std::cout << "Failed creting SDL window and renderer!\n";
    }

    SDL_SetWindowTitle(*window, "Breakout.exe");
}


void setLevelScene(bool** bricks,
    SDL_Rect& numOfLivesRect,
    SDL_Rect& levelNumRect,
    SDL_Rect& scoreRect,
    SDL_Rect& paddle,
    SDL_Rect& ball,
    SDL_Rect& brick,
    double& velocityY,
    double& velocityX,
    Level& levelObject) // it happens when entering new level
{
    for (unsigned int i = 0; i < (levelObject.getColumnCount() * levelObject.getRowCount()); i++)
    {
        if (levelObject.getBlockOfBricks()[i].getID() != "_")
        {
            *(*bricks + i) = true;
        }
        else
        {
            *(*bricks + i) = false;
        }
    }
    numOfLives++;

    numOfLivesRect.w = SCREEN_horizontal / 3; // one third of screen width
    numOfLivesRect.h = SCREEN_vertical / 10; // 10 percent of screen height
    numOfLivesRect.x = 0;
    numOfLivesRect.y = 0;

    levelNumRect.w = SCREEN_horizontal / 3; // one third of screen width
    levelNumRect.h = SCREEN_vertical / 10; // 10 percent of screen height
    levelNumRect.x = SCREEN_horizontal / 3;
    levelNumRect.y = 0;

    scoreRect.w = SCREEN_horizontal / 3; // one third of screen width
    scoreRect.h = SCREEN_vertical / 10; // 10 percent of screen height
    scoreRect.x = 2 * SCREEN_horizontal / 3;
    scoreRect.y = 0;

    paddle.h = SCREEN_vertical / 20; // set this adjustable to screen settings
    paddle.w = SCREEN_horizontal / 6;
    ball.w = paddle.h / 2;
    ball.h = ball.w;
    brick.w = (SCREEN_horizontal - (levelObject.getColumnSpacing() * (levelObject.getColumnCount() + 1))) / levelObject.getColumnCount();
    brick.h = static_cast<int>(0.1 * static_cast<double>((SCREEN_vertical - levelObject.getRowCount() * levelObject.getRowSpacing()) / levelObject.getRowCount()));

    // this block of code should be unique function, it is also called later, (ctrl + f)
    paddle.x = SCREEN_horizontal / 2 - paddle.w / 2;
    paddle.y = SCREEN_vertical - paddle.h - 10; // hardcoded 10 for making little space between bottom frame and the paddle
    ball.x = SCREEN_horizontal / 2 - ball.w / 2;
    ball.y = SCREEN_vertical - ball.h - paddle.h - 10; // -paddle.y - ball.h;
    velocityY = sqrt(2) * ballSpeed / 2; // if velocityY or X drops below 1, ball wont move in that axis
    velocityX = sqrt(2) * ballSpeed / 2;

    
}


void RestartFrame(int& lastFrame,
    int& lastTime,
    int& fps,
    int& frameCount)
{
    lastFrame = SDL_GetTicks(); // number of milliseconds since the SDL library initialized

    if (lastFrame >= lastTime + 1000)
    {
        lastTime = lastFrame;
        fps = frameCount;
        frameCount = 0;
    }
}


void RelativePositionBallPaddle(SDL_Rect& paddle,
    SDL_Rect& ball,
    double& velocityX,
    double& velocityY)
{
    float rel = static_cast<float>(paddle.x + (paddle.w / 2)) - (ball.x + (ball.w / 2));
    float angle = atan(rel / (paddle.w / 2));
    velocityY = -static_cast<double>(ballSpeed) * static_cast<double>(cos(angle));
    velocityX = -static_cast<double>(ballSpeed) * static_cast<double>(sin(angle));
}


void SetLimitSituations(SDL_Rect& paddle,
    SDL_Rect& ball,
    SDL_Rect& numOfLivesRect,
    double& velocityX,
    double& velocityY)
{
    if (paddle.x < 0)
    {
        paddle.x = 0;
    }

    if (paddle.x > static_cast<int>(SCREEN_horizontal) - paddle.w)
    {
        paddle.x = SCREEN_horizontal - paddle.w;
    }

    if (ball.y < numOfLivesRect.h)
    {
        ball.y = numOfLivesRect.h;
        velocityY = -velocityY;
    }

    if (ball.x < 0 || ball.x > static_cast<int>(SCREEN_horizontal) - ball.w)
    {
        velocityX = -velocityX;
    }

    if (ball.y + ball.h > static_cast<int>(SCREEN_vertical))
    {
        numOfLives--;

        paddle.x = SCREEN_horizontal / 2 - paddle.w / 2;
        paddle.y = SCREEN_vertical - paddle.h;
        ball.x = SCREEN_horizontal / 2 - ball.w / 2;
        ball.y = SCREEN_vertical - ball.h - paddle.h;
        velocityX = sqrt(2) * ballSpeed / 2;
        velocityY = sqrt(2) * ballSpeed / 2;
    }
}


void RelativePositionBallBrick(SDL_Rect& ball,
    SDL_Rect& brick,
    double& velocityX,
    double& velocityY)
{
    if (ball.x <= brick.x + brick.w / 2 && ball.x + ball.w >= brick.x)
    {
        if (static_cast<double>(ball.y) >= static_cast<double>(brick.y) + static_cast<double>(brick.h) - sqrt(pow(velocityY, 2) + pow(velocityX, 2)) - OFFSET) // TODO [lpavic]: whis condition should be implemented in all conditions where cordinates are checked
        {
            velocityY = abs(velocityY); // TODO [lpavic]: next 5 lines should be refactored in single function
            if (velocityX >= 0)
            {
                velocityX = -velocityX;
            }
        }
        else if (ball.y <= brick.y - ball.h )
        {
            velocityY = -velocityY;
            if (velocityX >= 0)
            {
                velocityX = -velocityX;
            }
        }
    }
    else if (ball.x + ball.w < brick.x )
    {
        if (ball.y >= brick.y + brick.h / 2)
        {
            velocityX = -velocityX;
            if (velocityY >= 0)
            {
                velocityY = -velocityY;
            }
        }
        else
        {
            velocityX = -velocityX;
            if (velocityY <= 0)
            {
                velocityY = -velocityY;
            }
        }
    }
    else if (ball.x > brick.x + brick.w / 2 && ball.x <= brick.x + brick.w)
    {
        if (ball.y >= brick.y + brick.h)
        {
            velocityY = -velocityY;
            if (velocityX <= 0)
            {
                velocityX = -velocityX;
            }
        }
        else
        {
            velocityY = -velocityY;
            if (velocityX <= 0)
            {
                velocityX = -velocityX;
            }
        }
    }
    else if (ball.x > brick.x + brick.w)
    {
        if (ball.y >= brick.y + brick.h / 2)
        {
            velocityX = -velocityX;
            if (velocityY >= 0)
            {
                velocityY = -velocityY;
            }
        }
        else
        {
            velocityX = -velocityX;
            if (velocityY <= 0)
            {
                velocityY = -velocityY;
            }
        }
    }
}


bool ReadInput(bool& isRunning,
    SDL_Event& event,
    SDL_Rect& paddle,
    double& velocityX,
    double& velocityY)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_QUIT)
    {
        isRunning = false;
        return true;
    }

    // TODO [lpavic]: implement Pause functionality; not working here yet
    /*
    if (keyboard[SDL_SCANCODE_P])
    {
        //SDL_Delay(1000);
        while (1)
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
                return true;
            }
            if (keyboard[SDL_SCANCODE_P])
            {
                break;
            }
        }
    }
    */

    if (keyboard[SDL_SCANCODE_LEFT])
    {
        paddle.x += -paddleSpeed;
    }

    if (keyboard[SDL_SCANCODE_RIGHT])
    {
        paddle.x += paddleSpeed;
    }

    if (keyboard[SDL_SCANCODE_DOWN])
    {
        if (sqrt(pow(velocityY, 2) + pow(velocityX, 2)) < 2.0 * static_cast<double>(ballSpeed))
        {
            velocityX *= sqrt(2); // TODO [lpavic]: implement better
            velocityY *= sqrt(2);
        }
    }
    return false;
    // alternative way, but slower
    /*
    if (event.type == SDL_KEYDOWN)
    {
        // std::cout << "A key has been pressed\n"; // for test purpose only

        if (event.key.keysym.sym == SDLK_DOWN)
        {
            std::cout << "Down key has been pressed\n";
            // TODO [lpavic]: Add funcionality to accelerate the ball
        }
        if (event.key.keysym.sym == SDLK_LEFT)
        {
            // std::cout << "Left key has been pressed\n";
            paddle.x += -paddleSpeed;
            // TODO [lpavic]: Add funcionality to move player to the left
        }
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            // std::cout << "Right key has been pressed\n";
            paddle.x += paddleSpeed;
            // TODO [lpavic]: Add funcionality to move player to the right
        }
    }
    */
}


void RefreshFrames(int& frameCount,
    int& lastFrame)
{
    int timerFPS;

    frameCount++;
    timerFPS = SDL_GetTicks() - lastFrame;

    if (timerFPS < (1000 / 50)) // TODO [lpavic]: make this dynamical so program doesnt lag
    {
        SDL_Delay((1000 / 50) - timerFPS);
    }
}


void DrawSurface(SDL_Rect& surfaceRect,
    SDL_Renderer** renderer,
    const char* displayString,
    TTF_Font** font,
    SDL_Color& color)
{
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = TTF_RenderText_Solid(*font, displayString, color);
    texture = SDL_CreateTextureFromSurface(*renderer, surface);

    surface->w = surfaceRect.w;
    surface->h = surfaceRect.h;

    SDL_RenderCopy(*renderer, texture, NULL, &surfaceRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


void DrawSprite(SDL_Renderer** renderer,
    SDL_Rect& target,
    std::string tempPath)
{
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = IMG_Load(tempPath.c_str());
    texture = SDL_CreateTextureFromSurface(*renderer, surface);

    surface->w = target.w;
    surface->h = target.h;

    SDL_RenderCopy(*renderer, texture, NULL, &target);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}