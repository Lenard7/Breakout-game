#pragma once

#include "Ball.h"
#include "Brick.h"
#include "LevelInformation.h"
#include "Menu.h"
#include "Paddle.h"

#include <memory>
#include <vector>

class Level
{
public:
	enum STATE
	{
		RUNNING = 0,
		PAUSED,
		QUIT,
		EXIT,
		Count
	};

	struct FrameInformation
	{
		int lastTime = 0;
		int frameCount = 0;
		int lastFrame;
		int fps;
	};

private:
	// attributes
    static Level * level;
    STATE state;
	// TODO [lpavic]: make this variable non-static member that is assigned by checking folder that contains level files
	static unsigned level_num;
	unsigned current_level{0};
	unsigned num_of_lives;
	unsigned total_score{0};

	// window data
	// TODO [lpavic]: this window maybe should be shared pointer!?
    // values of window variable and its dimensions are passed through constructor
    SDL_Window* window;
    unsigned window_horizontal_size;
    unsigned window_vertical_size;
    SDL_Renderer* renderer{nullptr};
	// offset variable as offset in dimensions of window
	unsigned offset{0};
	FrameInformation frame_information{0};

	// TODO [lpavic]: use snake case variable names
	// data extracted from xml files
	unsigned rowCount;
	unsigned columnCount;
	unsigned rowSpacing;
	unsigned columnSpacing;
	// this is image of board // TODO [lpavic]: this variable is unused (load unique image (.dds file) (instead of making path inside program))
	std::string backgroundTexture;
	std::string bricks_string{""};
	
	// gameplay data
	// TODO [lpavic]: see if polymorphism and upcasting should be used - maybe use array of GameElement objects and upcast them to derived class?
	std::unique_ptr<Brick[]> bricks{nullptr};
	unsigned num_of_bricks{0};
	Paddle paddle;
	Ball ball;
	std::unique_ptr<LevelInformation[]> level_information{nullptr};
	unsigned num_of_level_information{0};
	bool level_victory{false};

	Level(SDL_Window** window, unsigned& window_horizontal_size, unsigned& window_vertical_size);
	~Level();

	// TODO [lpavic]: use lower camel case names for functions
	void drawLevel();
	void handleKeyboardStates(const Uint8 const* keyboard);
	void parseLevelFile(tinyxml2::XMLDocument & doc);
	void printLevel() const;
	void refreshFrames();
	void relativePositionBallBrick(const unsigned & i);
	void relativePositionBallPaddle();
	void restartFrame();
	void setLevelScene();
	void setLimitSituations();

public:
	static Level * getInstance(SDL_Window** window, 
                                unsigned& window_horizontal_size,
                                unsigned& window_vertical_size);
	Level(const Level&) = delete;
	Level & operator = (const Level &) = delete;
	void destroy();

    // this method is implemented as state machine
	STATE runImplementation();

	// setters and getters
    inline const STATE getState() const { return state; }
	const unsigned getRowCount() const;
	const unsigned getColumnCount() const;
	const unsigned getRowSpacing() const;
	const unsigned getColumnSpacing() const;
	const std::string getBackgroundTexture() const;
	const unsigned getNumOfBricks() const;
	const Brick* getBricks() const;

    inline void setState(const STATE state) { this->state = state; }
};
