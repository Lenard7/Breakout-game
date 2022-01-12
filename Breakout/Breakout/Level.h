#pragma once

#include <iostream>
#include <vector>

#pragma warning(push, 0)
#include "tinyxml2.h"
#pragma warning(pop)
#include "BrickType.h"

class Level
{
private:
	unsigned int rowCount;
	unsigned int columnCount;
	unsigned int rowSpacing;
	unsigned int columnSpacing;
	std::string backgroundTexture;
	BrickType brickType[5];
	std::string bricks;

	unsigned int numOfBricks;
	std::vector<BrickType> blockOfBricks;
public:
	Level();
	Level(tinyxml2::XMLDocument& doc);
	~Level();

	void PrintLevel();
	unsigned int getRowCount();
	unsigned int getColumnCount();
	unsigned int getRowSpacing();
	unsigned int getColumnSpacing();
	std::string getBackgroundTexture();
	unsigned int getNumOfBricks();
	std::vector<BrickType> getBlockOfBricks();
	std::vector<BrickType>& getPointerToBlockOfBricks();
};