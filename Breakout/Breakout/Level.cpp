// this #define is needed because of error when snprintf or strcpy was used: "This function or variable may be unsafe"
#define _CRT_SECURE_NO_WARNINGS

#include "ErrorHandler.h"
#include "Level.h"
#include "PauseMenu.h"
#include "Resources.h"

#include "tinyxml2.h"

#include <iostream>


Level * Level::level = nullptr;
// TODO [lpavic]: make this variable non-static member that is assigned by checking folder that contains level files
unsigned Level::level_num = 3;


// TODO [lpavic]: see if some methods should be actually in constructor - e.g. setLevelScene initializes some variables that maybee can be initialized inside constructor
Level::Level(SDL_Window** window,
			unsigned& window_horizontal_size,
			unsigned& window_vertical_size) : state(Level::RUNNING)
{
	this->window = *window;
	this->window_horizontal_size = window_horizontal_size;
	this->window_vertical_size = window_vertical_size;
	this->offset = static_cast<int>(std::min(window_vertical_size, window_horizontal_size) * 0.01);

	if (Level::level_num < 1)
	{
		THROW_FAILURE("Level configuration invalid or corrupted!\n");
	}
	else if (Level::level_num >= 1 && Level::level_num < 4)
	{
		this->num_of_lives = Level::level_num - 1;
	}
	else
	{
		this->num_of_lives = 3;
	}
}

Level::~Level()
{

}


Level * Level::getInstance(SDL_Window** window,
                                    unsigned& window_horizontal_size,
                                    unsigned& window_vertical_size)
{
    if (level == nullptr)
    {
        level = new Level(window, window_horizontal_size, window_vertical_size);
    }
    return level;
}


void Level::destroy()
{
	if (this->level)
    {
        delete this->level;
        this->level = nullptr;
    }
}


Level::STATE Level::runImplementation()
{
	for (this->current_level = 0; this->current_level < this->level_num; ++(this->current_level))
	{
		tinyxml2::XMLDocument doc;
		char* levelFileName;
		size_t fileNameLength;
		char* levelOrdinalNum;

		// TODO [lpavic]: this reading of file should be done in C++ style (avoid malloc and free functions)
		levelOrdinalNum = (char*) malloc((int)(floor(log10(current_level + 1) + 2)));
		snprintf(levelOrdinalNum, (int)(floor(log10(current_level + 1) + 2)), "%u", current_level + 1);

		fileNameLength = strlen(Resources::level_resources) + strlen("Level") + strlen(levelOrdinalNum) + strlen(".xml") + 1;
		levelFileName = (char*)malloc(sizeof(char*) * fileNameLength);
		snprintf(levelFileName, fileNameLength, "%s%s%s%s", Resources::level_resources, "Level", levelOrdinalNum, ".xml");
		
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

		if (doc.LoadFile(fp) != tinyxml2::XML_SUCCESS)
		{
			THROW_FAILURE("Error while parsing xml level file");
		}

		if (levelFileName)
		{
			free(levelFileName);
			levelFileName = NULL;
		}
		if (levelOrdinalNum)
		{
			free(levelOrdinalNum);
			levelOrdinalNum = NULL;
		}

		ParseLevelFile(doc);
		if (fp)
		{
			fclose(fp);
		}

		setLevelScene();

		this->renderer = SDL_CreateRenderer(window, -1, 0);
		if(this->renderer == NULL)
		{
			THROW_FAILURE("Error while creating renderer for level!\n");
		}

		SDL_Event event;
		this->level_victory = false;
		while (!this->level_victory)
		{
			// TODO [lpavic]: the game is much slower with calling this function
			// restartFrame();
			
			if (this->num_of_lives < 1)
			{
				if (this->renderer)
				{
					SDL_DestroyRenderer(renderer);
				}
				this->setState(Level::QUIT);
				return Level::STATE::QUIT;
			}

			if (SDL_HasIntersection(&(this->paddle.getTexture()), &(this->ball.getTexture())))
			{
			/* TODO [lpavic]: make method that handles producing sound
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
			*/
				
				relativePositionBallPaddle();
			}

			setLimitSituations();

			SDL_Rect temp = this->ball.getTexture();
			temp.x += static_cast<int>(this->ball.getVelocityX());
			temp.y += static_cast<int>(this->ball.getVelocityY());
			this->ball.setTexture(temp);
			
			this->level_victory = true;
			for (unsigned i = 0; i < this->num_of_bricks; ++i)
			{
				if (SDL_HasIntersection(&(this->ball.getTexture()), &(this->bricks[i].getTexture())) && this->bricks[i].getIsAlive())
                {
					/* 
					// TODO [lpavic]: make method that handles producing sound
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
					*/
					if (this->bricks[i].getID() != "I" && this->bricks[i].getIsAlive())
					{
						int temp_hit_points = std::stoi(this->bricks[i].getHitPoints());
						temp_hit_points--;
						bricks[i].setHitPoints(std::to_string(temp_hit_points));
						if (temp_hit_points <= 0)
						{
							this->bricks[i].setIsAlive(false);
							this->total_score += this->bricks[i].getBreakScore();
						}
					}

					relativePositionBallBrick(i);
				}
				if (this->bricks[i].getIsAlive() && bricks[i].getID() != "I")
				{
					this->level_victory = false;
				}
			}

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					return STATE::EXIT;
				}

				const Uint8* keyboard = SDL_GetKeyboardState(NULL);

				if (keyboard[SDL_SCANCODE_ESCAPE])
				{
					if (this->renderer)
					{
       					SDL_DestroyRenderer(renderer);
					}

					PauseMenu * pause_menu = PauseMenu::getInstance(&window, 
													window_horizontal_size, 
													window_vertical_size);
					this->setState(Level::PAUSED);
					while(this->getState() == Level::PAUSED)
					{
						switch(pause_menu->runImplementation())
						{
							case PauseMenu::CONTINUE:
								pause_menu->destroy();
								this->setState(Level::RUNNING);
								this->renderer = SDL_CreateRenderer(window, -1, 0);
								if(this->renderer == NULL)
								{
									THROW_FAILURE("Error while creating renderer for level!\n");
								}
								// do not return, setLevelState to continue and check later,
									// if Continue, do not call for Level destructor
								break;
							
							// case PauseMenu::RESTART:
							// 	pause_menu->destroy();
							// 	// do not return, setLevelState to restart and check later,
							// 		// if Restart, do call for Level destructor and call it again
							// 	break;
							
							case PauseMenu::QUIT:
								pause_menu->destroy();
								this->setState(Level::QUIT);
								return Level::STATE::QUIT;
								break;

							case PauseMenu::EXIT:
								pause_menu->destroy();
								this->setState(Level::EXIT);
								return Level::STATE::EXIT;
								break;

							case PauseMenu::Count:
								THROW_FAILURE("Count state for main menu not valid!\n");
								break;
							
							default:
								THROW_FAILURE("Main menu is in no state!\n");
						}
					}
				}
			}
			/** https://stackoverflow.com/questions/29373203/sdl-2-0-key-repeat-and-delay
			 * reading from keyboard should not be inside 
			 * while (SDL_PollEvent) loop because of
			 * first delay when pressing one button for longer
			 * time
			 */
			const Uint8* keyboard = SDL_GetKeyboardState(NULL);
			handleKeyboardStates(keyboard);

			drawLevel();
		}
		if (this->level_victory)
		{
			// TODO [lpavic]: clear Renderer of Level and other pointers related to current level
        	SDL_DestroyRenderer(this->renderer);
		}
	}

	// TODO [lpavic]: see if this needs to be put inside destructor of Level
	if (this->renderer)
	{
		SDL_DestroyRenderer(renderer);
	}
	this->setState(Level::QUIT);
	return Level::STATE::QUIT;
}

void Level::drawLevel()
{
	if (SDL_SetRenderDrawColor(this->renderer, 20, 20, 20, 255) != 0)
	{
		THROW_FAILURE("Setting render draw color error!\n");
	}
	if (SDL_RenderClear(this->renderer) != 0)
	{
		THROW_FAILURE("Clearing level renderer error!\n");
	}

	// TODO [lpavic]: see if this is needed
	RefreshFrames();

	this->ball.DrawSprite(&this->renderer);
	this->paddle.DrawSprite(&this->renderer);
	
	// TODO [lpavic]: whole game lags when there are more bricks
	for (unsigned i = 0; i < this->num_of_bricks; i++)
	{
		if (this->bricks[i].getIsAlive())
		{
			this->bricks[i].DrawSprite(&this->renderer);
		}
	}

	// TODO [lpavic]: display lives, score and level as multiline string
	// TODO [lpavic]: implement drawing lives, score and level
	this->level_information[0].drawSurface(&(this->renderer), std::to_string(this->num_of_lives));
	this->level_information[1].drawSurface(&(this->renderer), std::to_string(this->current_level + 1));
	this->level_information[2].drawSurface(&(this->renderer), std::to_string(this->total_score));

	SDL_RenderPresent(this->renderer);
}


void Level::handleKeyboardStates(const Uint8 const* keyboard)
{
	SDL_Rect temp = this->paddle.getTexture();
	if (keyboard[SDL_SCANCODE_LEFT])
	{
		temp.x += -this->paddle.getVelocityX();
		this->paddle.setTexture(temp);
	}

	if (keyboard[SDL_SCANCODE_RIGHT])
	{
		temp.x += this->paddle.getVelocityX();
		this->paddle.setTexture(temp);
	}

	// TODO [lpavic]: implement better
	// if (keyboard[SDL_SCANCODE_DOWN])
	// {
	// 	if (sqrt(pow(this->ball.getVelocityY(), 2) + pow(this->ball.getVelocityX(), 2)) 
	// 		< 1.05 * static_cast<double>(sqrt(pow(this->window_horizontal_size, 2) + pow(this->window_vertical_size, 2))))
	// 	{
	// 		this->ball.setVelocityX(1.05 * this->ball.getVelocityX());
	// 		this->ball.setVelocityY(1.05 * this->ball.getVelocityY());
	// 	}
	// }
}


void Level::ParseLevelFile(tinyxml2::XMLDocument & doc)
{
	tinyxml2::XMLElement* rootElement = doc.FirstChildElement("Level");
	if (rootElement == NULL)
	{
		THROW_FAILURE("Level element in xml file not found!");
	}	
	this->rowCount = rootElement->UnsignedAttribute("RowCount");
	this->columnCount = rootElement->UnsignedAttribute("ColumnCount");
	this->rowSpacing = rootElement->UnsignedAttribute("RowSpacing");
	this->columnSpacing = rootElement->UnsignedAttribute("ColumnSpacing");
	this->backgroundTexture = rootElement->Attribute("BackgroundTexture");

	tinyxml2::XMLElement* brick_types = rootElement->FirstChildElement("BrickTypes");
	if (brick_types == NULL)
	{
		THROW_FAILURE("BrickTypes element in xml file not found!");
	}
	
	this->bricks = std::make_unique<Brick[]>(this->rowCount * this->columnCount);

	tinyxml2::XMLElement* brick_type = brick_types->FirstChildElement("BrickType");
	// vector of all types of bricks inside Level (if all bricks inside level are Soft, this vector will only have 2 elements with ID 'S' and '_')
	std::vector<Brick> brick_type_temp;
	for (;brick_type != nullptr; brick_type = brick_type->NextSiblingElement("BrickType"))
	{
		bool id_exists = false;
		for(std::vector<Brick>::iterator it = brick_type_temp.begin(); it != brick_type_temp.end(); ++it)
		{
			if (it->getID() == brick_type->Attribute("Id"))
			{
				id_exists = true;
			}
		}
		if (!id_exists)
		{
			Brick brick_type_object(*brick_type);
			brick_type_temp.push_back(brick_type_object);
		}
	}

	// "_" is not actually a brick type, but only placeholder in Bricks_string for a place in game where there is no brick
	Brick brick_temp;
	brick_temp.setID("_");
	brick_type_temp.push_back(brick_temp);

	tinyxml2::XMLElement* bricks = rootElement->FirstChildElement("Bricks");
	if (brick_types == NULL)
	{
		THROW_FAILURE("Bricks element in xml file not found!");
	}
	this->bricks_string = bricks->GetText();
	this->num_of_bricks = this->rowCount * this->columnCount; // empty spaces are special kind of bricks which are not going to be drawn and their HP = 0;

	unsigned temp_brick_count = 0;
	for (unsigned size_of_bricks_string = 0; size_of_bricks_string < static_cast<unsigned int>(this->bricks_string.size()) && temp_brick_count < this->num_of_bricks; ++size_of_bricks_string)
	{
		for (unsigned j = 0; j < brick_type_temp.size(); ++j)
		{
			if (brick_type_temp[j].getID() == std::string(1, this->bricks_string[size_of_bricks_string]))
			{
				this->bricks[temp_brick_count] = brick_type_temp[j];
				temp_brick_count++;
			}
		}
	}

	PrintLevel();
}


void Level::PrintLevel() const // TODO [lpavic]: finish printing all attributes of class Level
{
	std::cout << "Row Count : " << this->rowCount << "\n"
		<< "Column Count : " << this->columnCount << "\n"
		<< "Row Spacing : " << this->rowSpacing << "\n"
		<< "Column Spacing : " << this->columnSpacing << "\n"
		<< "Background Texture : " << this->backgroundTexture << "\n\n";

	if (bricks)
	{
		for (unsigned int i = 0; i < this->rowCount * this->columnCount; ++i)
		{
			std::cout << i + 1 << ".\n";
			std::cout << this->bricks[i].getID() << "\n"
				<< this->bricks[i].getTexturePath() << "\n"
				<< this->bricks[i].getHitPoints() << "\n"
				<< this->bricks[i].getHitSound() << "\n";
		}
	}
}


void Level::RefreshFrames()
{
    int timerFPS;

	this->frame_information.frameCount++;
    timerFPS = SDL_GetTicks() - this->frame_information.lastFrame;

    // TODO [lpavic]: make this dynamical, not hardcoded
    if (timerFPS < (1000 / 60))
    {
        SDL_Delay((1000 / 60) - timerFPS);
    }
}


void Level::relativePositionBallBrick(const unsigned & i)
{
	if(this->ball.getTexture().x <= this->bricks[i].getTexture().x + this->bricks[i].getTexture().w / 2
		&& this->ball.getTexture().x + this->ball.getTexture().w >= this->bricks[i].getTexture().x)
    {
        // TODO [lpavic]: this condition should be implemented in all conditions where cordinates are checked
        if (static_cast<double>(this->ball.getTexture().y) 
			>= static_cast<double>(this->bricks[i].getTexture().y) + static_cast<double>(this->bricks[i].getTexture().h) 
			- sqrt(pow(this->ball.getVelocityY(), 2) + pow(this->ball.getVelocityX(), 2)) - this->offset)
        {
            this->ball.setVelocityY(abs(this->ball.getVelocityY()));
            if (this->ball.getVelocityX() >= 0)
            {
				this->ball.setVelocityX(-this->ball.getVelocityX());
            }
        }
		else if (this->ball.getTexture().y <= this->bricks[i].getTexture().y - this->ball.getTexture().h)
        {
			this->ball.setVelocityY(-this->ball.getVelocityY());
            if (this->ball.getVelocityX() >= 0)
            {
				this->ball.setVelocityX(-this->ball.getVelocityX());
            }
        }
    }
    else if (this->ball.getTexture().x + this->ball.getTexture().w < this->bricks[i].getTexture().x )
    {
        if (this->ball.getTexture().y >= this->bricks[i].getTexture().y + this->bricks[i].getTexture().h / 2)
        {
            this->ball.setVelocityX(-this->ball.getVelocityX());
            if (this->ball.getVelocityY() >= 0)
            {
				this->ball.setVelocityY(-this->ball.getVelocityY());
            }
        }
        else
        {
			this->ball.setVelocityX(-this->ball.getVelocityX());
            if (this->ball.getVelocityY() <= 0)
            {
				this->ball.setVelocityY(-this->ball.getVelocityY());
            }
        }
    }
    else if (this->ball.getTexture().x > this->bricks[i].getTexture().x + this->bricks[i].getTexture().w / 2 
		&& this->ball.getTexture().x <= this->bricks[i].getTexture().x + this->bricks[i].getTexture().w)
    {
        if (this->ball.getTexture().y >= this->bricks[i].getTexture().y + this->bricks[i].getTexture().h)
        {
			this->ball.setVelocityY(-this->ball.getVelocityY());
            if (this->ball.getVelocityX() <= 0)
            {
				this->ball.setVelocityX(-this->ball.getVelocityX());
            }
        }
        else
        {
			this->ball.setVelocityY(-this->ball.getVelocityY());
            if (this->ball.getVelocityX() <= 0)
            {
				this->ball.setVelocityX(-this->ball.getVelocityX());
            }
        }
    }
    else if (this->ball.getTexture().x > this->bricks[i].getTexture().x + this->bricks[i].getTexture().w)
    {
        if (this->ball.getTexture().y >= this->bricks[i].getTexture().y + this->bricks[i].getTexture().h / 2)
        {
			this->ball.setVelocityX(-this->ball.getVelocityX());
            if (this->ball.getVelocityY() >= 0)
            {
				this->ball.setVelocityY(-this->ball.getVelocityY());
            }
        }
        else
        {
			this->ball.setVelocityX(-this->ball.getVelocityX());
            if (this->ball.getVelocityY() <= 0)
            {
				this->ball.setVelocityY(-this->ball.getVelocityY());
            }
        }
    }
}


void Level::relativePositionBallPaddle()
{
	double rel = static_cast<float>(this->paddle.getTexture().x + (this->paddle.getTexture().w / 2)) - (this->ball.getTexture().x + (this->ball.getTexture().w / 2));
    double angle = static_cast<double>(atan(rel / (this->paddle.getTexture().w / 2)));
	double ball_speed = sqrt(pow(this->ball.getVelocityX(), 2) + pow(this->ball.getVelocityY(), 2));
	this->ball.setVelocityX(-static_cast<double>(ball_speed) * static_cast<double>(sin(angle)));
	this->ball.setVelocityY(-static_cast<double>(ball_speed) * static_cast<double>(cos(angle)));
}


void Level::restartFrame()
{
	// number of milliseconds since the SDL library initialized
    this->frame_information.lastFrame = SDL_GetTicks();

    if (this->frame_information.lastFrame >= this->frame_information.lastTime + 100)
    {
        this->frame_information.lastTime = this->frame_information.lastFrame;
        this->frame_information.fps = this->frame_information.frameCount;
        this->frame_information.frameCount = 0;
    }
}


void Level::setLevelScene()
{
    this->num_of_lives++;

	this->num_of_level_information = 3;
	this->level_information = std::make_unique<LevelInformation[]>(this->num_of_level_information);

	// TODO [lpavic]: see that temp_rect is initialized in 1 line just like temp_color struct
	SDL_Rect temp_rect;
	SDL_Color temp_color{255, 255, 255};

	// one third of screen width
    temp_rect.w = this->window_horizontal_size / 3;
    // 10 percent of screen height
    temp_rect.h = this->window_vertical_size / 10;
    temp_rect.x = 0;
    temp_rect.y = 0;
	// TODO [lpavic]: apply "rule of five" in definition of LevelInformation class
	this->level_information[0] = std::move(LevelInformation(temp_rect, std::string("arial.ttf"), 100, 
												  std::string("Lives: "), temp_color));

    // one third of screen width
    temp_rect.w = this->window_horizontal_size / 3;
    // 10 percent of screen height
    temp_rect.h = this->window_vertical_size / 10;
    temp_rect.x = this->window_horizontal_size / 3;
    temp_rect.y = 0;
	this->level_information[1] = LevelInformation(temp_rect, std::string("arial.ttf"), 100, 
												  std::string("Level: "), temp_color);

    // one third of screen width
    temp_rect.w = this->window_horizontal_size / 3;
    // 10 percent of screen height
    temp_rect.h = this->window_vertical_size / 10;
    temp_rect.x = 2 * this->window_horizontal_size / 3;
    temp_rect.y = 0;
	this->level_information[2] = LevelInformation(temp_rect, std::string("arial.ttf"), 100, 
												  std::string("Score: "), temp_color);

    // // one third of screen width
    // this->level_information.numOfLivesRect.w = this->window_horizontal_size / 3;
    // // 10 percent of screen height
    // this->level_information.numOfLivesRect.h = this->window_vertical_size / 10;
    // this->level_information.numOfLivesRect.x = 0;
    // this->level_information.numOfLivesRect.y = 0;

    // // one third of screen width
    // this->level_information.levelNumRect.w = this->window_horizontal_size / 3;
    // // 10 percent of screen height
    // this->level_information.levelNumRect.h = this->window_vertical_size / 10;
    // this->level_information.levelNumRect.x = this->window_horizontal_size / 3;
    // this->level_information.levelNumRect.y = 0;

    // // one third of screen width
    // this->level_information.scoreRect.w = this->window_horizontal_size / 3;
    // // 10 percent of screen height
    // this->level_information.scoreRect.h = this->window_vertical_size / 10;
    // this->level_information.scoreRect.x = 2 * this->window_horizontal_size / 3;
    // this->level_information.scoreRect.y = 0;

    // set this adjustable to screen settings
	temp_rect.w = this->window_horizontal_size / 6;
    temp_rect.h = this->window_vertical_size / 20;
	temp_rect.x = this->window_horizontal_size / 2 - temp_rect.w / 2;
	// hardcoded 10 for making little space between bottom frame and the paddle
    temp_rect.y = this->window_vertical_size - temp_rect.h - 10;
	this->paddle.setTexture(temp_rect);
	this->paddle.setVelocityX(this->window_horizontal_size * 0.005);

    temp_rect.w = this->paddle.getTexture().h / 2;
    temp_rect.h = temp_rect.w;
	temp_rect.x = this->window_horizontal_size / 2 - temp_rect.w / 2;
    // -paddle.y - ball.h
    temp_rect.y = this->window_vertical_size - temp_rect.h - this->paddle.getTexture().h - 10;
	this->ball.setTexture(temp_rect);
	// if velocityY or X drops below 1, ball wont move in that axis
	// TODO [lpavic]: if there are more bricks, ball and paddle will move slowly
	this->ball.setVelocityX(this->window_horizontal_size * 0.003);
	this->ball.setVelocityY(this->window_vertical_size * 0.003);

	for (unsigned int i = 0; i < (this->getColumnCount() * this->getRowCount()); ++i)
    {
        if (this->bricks[i].getID() != "_")
        {
            this->bricks[i].setIsAlive(true);
        }
        else
        {
            this->bricks[i].setIsAlive(false);
        }

		temp_rect.w = (this->window_horizontal_size - (this->getColumnSpacing() * (this->getColumnCount() + 1))) / this->getColumnCount();
		temp_rect.h = static_cast<int>(0.1 * static_cast<double>((this->window_vertical_size - this->getRowCount() * this->getRowSpacing()) / this->getRowCount()));
		temp_rect.x = (i % this->getColumnCount()) * (temp_rect.w + this->getColumnSpacing()) + this->getColumnSpacing() / 2;
		temp_rect.y = this->level_information[0].getTexture().h + (i / this->getColumnCount()) * (temp_rect.h + this->getRowSpacing()) + this->getRowSpacing() / 2;
		this->bricks[i].setTexture(temp_rect);
    }
}


void Level::setLimitSituations()
{
	SDL_Rect temp_rect;
	
	if (this->paddle.getTexture().x < 0)
    {
		temp_rect = this->paddle.getTexture();
		temp_rect.x = 0;
        this->paddle.setTexture(temp_rect);
    }

    if (this->paddle.getTexture().x > static_cast<int>(window_horizontal_size) - this->paddle.getTexture().w)
    {
		temp_rect = this->paddle.getTexture();
		temp_rect.x = window_horizontal_size - this->paddle.getTexture().w;
        this->paddle.setTexture(temp_rect);
    }

    if (this->ball.getTexture().y < this->level_information[0].getTexture().h)
    {
        temp_rect = this->ball.getTexture();
		temp_rect.y = this->level_information[0].getTexture().h;
		this->ball.setTexture(temp_rect);
        ball.setVelocityY(ball.getVelocityY() * (-1));
    }

    if (this->ball.getTexture().x < 0 || this->ball.getTexture().x > static_cast<int>(window_horizontal_size) - this->ball.getTexture().w)
    {
        this->ball.setVelocityX(this->ball.getVelocityX() * (-1));
    }

    if (this->ball.getTexture().y + this->ball.getTexture().h > static_cast<int>(window_vertical_size))
    {
        this->num_of_lives--;

		temp_rect = this->paddle.getTexture();
        temp_rect.x = window_horizontal_size / 2 - this->paddle.getTexture().w / 2;
        temp_rect.y = window_vertical_size - this->paddle.getTexture().h;
        this->paddle.setTexture(temp_rect);

		temp_rect = this->ball.getTexture();
		temp_rect.x = window_horizontal_size / 2 - this->ball.getTexture().w / 2;
        temp_rect.y = window_vertical_size - this->ball.getTexture().h - this->paddle.getTexture().h;
        this->ball.setTexture(temp_rect);
        this->ball.setVelocityX(this->window_horizontal_size * 0.003);
        this->ball.setVelocityY(this->window_vertical_size * 0.003);
    }
}


// TODO [lpavic]: put these functions in header as inline functions 
const unsigned Level::getRowCount() const { return this->rowCount; }
const unsigned int Level::getColumnCount() const { return this->columnCount; }
const unsigned int Level::getRowSpacing() const { return this->rowSpacing; }
const unsigned int Level::getColumnSpacing() const { return this->columnSpacing; }
const std::string Level::getBackgroundTexture() const { return this->backgroundTexture; }
const unsigned int Level::getNumOfBricks() const { return this->num_of_bricks; }
