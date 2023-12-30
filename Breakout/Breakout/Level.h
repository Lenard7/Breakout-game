#pragma once

#include "Ball.h"
#include "Brick.h"
#include "LevelInformation.h"
#include "Menu.h"
#include "Paddle.h"

#include <memory>
#include <vector>


// this class is made as singleton
class Level
{
public:
	enum class STATE
	{
		RUNNING = 0,
		PAUSED,
		QUIT,
		EXIT,
		Count
	};

	struct FrameInformation
	{
		int last_time = 0;
		int frame_count = 0;
		int last_frame = 0;
		int fps = 0;
	};

private:
	// attributes
    static Level* level;
    STATE state{STATE::RUNNING};
	// TODO [lpavic]: make this variable non-static member that is assigned by checking folder that contains level files
	// TODO [lpavic]: getter and setter for static member?
	static unsigned level_num;
	unsigned current_level{0};
	unsigned num_of_lives{0};
	unsigned total_score{0};

	// window data
	// TODO [lpavic]: this window maybe should be shared pointer!?
    // values of window variable and its dimensions are passed through constructor
    SDL_Window* window{nullptr};
    unsigned window_horizontal_size{0};
    unsigned window_vertical_size{0};
	// TODO [lpavic]: this renderer maybe should be unique pointer!?
    SDL_Renderer* renderer{nullptr};
	// offset variable as offset in dimensions of window
	// TODO [lpavic]: unused variable?
	unsigned offset{0};
	FrameInformation frame_information{0};

	// data extracted from xml files
	unsigned row_count{0};
	unsigned column_count{0};
	unsigned row_spacing{0};
	unsigned column_spacing{0};
	// this is image of board // TODO [lpavic]: this variable is unused (load unique image (.dds file) (instead of making path inside program))
	std::string background_texture{""};
	std::string bricks_string{""};
	
	// gameplay data
	// TODO [lpavic]: see if polymorphism and upcasting should be used - maybe use array of GameElement objects and upcast them to derived class?
	std::unique_ptr<Brick[]> bricks{nullptr};
	unsigned num_of_bricks{0};
	Paddle paddle{};
	Ball ball{};
	std::unique_ptr<LevelInformation[]> level_information{nullptr};
	unsigned num_of_level_information{0};
	bool level_victory{false};

	Level(SDL_Window* const * const window, const unsigned& window_horizontal_size, const unsigned& window_vertical_size);
	~Level();

	void drawLevel();
	void handleKeyboardStates(const Uint8* const keyboard) noexcept;
	void parseLevelFile(const tinyxml2::XMLDocument& doc);
	void printLevel() const noexcept;
	void refreshFrames();
	void relativePositionBallBrick(const unsigned& i) noexcept;
	void relativePositionBallPaddle() noexcept;
	void restartFrame();
	void setLevelScene();
	void setLimitSituations() noexcept;

public:
	static Level* getInstance(SDL_Window* const * const window, 
                                const unsigned& window_horizontal_size,
                                const unsigned& window_vertical_size);
	Level(const Level& level) = delete;
	Level(Level&& level);
	Level& operator =(const Level& level) = delete;
	Level& operator =(Level&& level);
	void destroy();

    // this method is implemented as state machine
	STATE runImplementation();

	// getters and setters
    inline const STATE& getState() const noexcept { return this->state; }
    inline const unsigned& getCurrentLevel() const noexcept { return this->current_level; }
    inline const unsigned& getNumOfLives() const noexcept { return this->num_of_lives; }
    inline const unsigned& getTotalScore() const noexcept { return this->total_score; }

	// TODO [lpavic]: there is no const since there would need const_cast for SDL_Window* a = this->getWindow(); invokation - better to use smart pointers in classes
	inline SDL_Window* getWindow() const noexcept { return this->window; }
    inline const unsigned& getWindowHorizontalSize() const noexcept { return this->window_horizontal_size; }
    inline const unsigned& getWindowVerticalSize() const noexcept { return this->window_vertical_size; }
	// TODO [lpavic]: use smart pointer
    inline SDL_Renderer* getRenderer() const noexcept { return this->renderer; }
    inline const unsigned& getOffset() const noexcept { return this->offset; }
    inline const FrameInformation& getFrameInformation() const noexcept { return this->frame_information; }

	inline const unsigned& getRowCount() const noexcept { return this->row_count; }
	inline const unsigned& getColumnCount() const noexcept { return this->column_count; }
	inline const unsigned& getRowSpacing() const noexcept { return this->row_spacing; }
	inline const unsigned& getColumnSpacing() const noexcept { return this->column_spacing; }
	inline const std::string& getBackgroundTexture() const noexcept { return this->background_texture; }
	inline const std::string& getBricksString() const noexcept { return this->bricks_string; }

	inline const std::unique_ptr<Brick[]>& getBricks() const noexcept { return this->bricks; }
	inline std::unique_ptr<Brick[]>& getBricks() noexcept { return this->bricks; }
	inline const unsigned& getNumOfBricks() const noexcept { return this->num_of_bricks; }
	inline const Paddle& getPaddle() const noexcept { return this->paddle; }
	inline const Ball& getBall() const noexcept { return this->ball; }
	inline const std::unique_ptr<LevelInformation[]>& getLevelInformation() const noexcept { return this->level_information; }
	inline std::unique_ptr<LevelInformation[]>& getLevelInformation() noexcept { return this->level_information; }
	inline const unsigned& getNumOfLevelInformation() const noexcept { return this->num_of_level_information; }
	inline const bool getLevelVictory() const noexcept { return this->level_victory; }

    inline void setState(const STATE& state) noexcept { this->state = state; }
    inline void setCurrentLevel(const unsigned& current_level) noexcept { this->current_level = current_level; }
    inline void setNumOfLives(const unsigned& num_of_lives) noexcept { this->num_of_lives = num_of_lives; }
    inline void setTotalScore(const unsigned& total_score) noexcept { this->total_score = total_score; }

	// TODO [lpavic]: use smart pointer
	inline void setWindow(SDL_Window* const window ) noexcept { this->window = window; }
    inline void setWindowHorizontalSize(const unsigned& window_horizontal_size ) noexcept { this->window_horizontal_size = window_horizontal_size; }
    inline void setWindowVerticalSize(const unsigned& window_vertical_size ) noexcept { this->window_vertical_size = window_vertical_size; }
	// TODO [lpavic]: use smart pointer
    inline void setRenderer(SDL_Renderer* const renderer ) noexcept { this->renderer = renderer; }
    inline void setOffset(const unsigned& offset ) noexcept { this->offset = offset; }
    inline void setFrameInformation(const FrameInformation& frame_information ) noexcept { this->frame_information = frame_information; }

	inline void setRowCount(const unsigned& row_count) noexcept { this->row_count = row_count; }
	inline void setColumnCount(const unsigned& column_count) noexcept { this->column_count = column_count; }
	inline void setRowSpacing(const unsigned& row_spacing) noexcept { this->row_spacing = row_spacing; }
	inline void setColumnSpacing(const unsigned& column_spacing) noexcept { this->column_spacing = column_spacing; }
	inline void setBackgroundTexture(const std::string& background_texture) noexcept { this->background_texture = background_texture; }
	inline void setBricksString(const std::string& bricks_string) noexcept { this->bricks_string = bricks_string; }

	inline void setBricks(std::unique_ptr<Brick[]>&& bricks) noexcept { this->bricks = std::move(bricks); }
	inline void setNumOfBricks(const unsigned& num_of_bricks) noexcept { this->num_of_bricks = num_of_bricks; }
	inline void setPaddle(const Paddle& paddle) noexcept { this->paddle = paddle; }
	inline void setBall(const Ball& ball) noexcept { this->ball = ball; }
	inline void setLevelInformation(std::unique_ptr<LevelInformation[]>&& level_information) noexcept { this->level_information = std::move(level_information); }
	inline void setNumOfLevelInformation(const unsigned& num_of_level_information) noexcept { this->num_of_level_information = num_of_level_information; }
	inline void setLevelVictory(const bool level_victoryl) noexcept { this->level_victory = level_victory; }
};
