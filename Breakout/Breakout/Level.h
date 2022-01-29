#pragma once

#include <iostream>
#include <vector>

// TODO [lpavic]: write comment why is this pragma added to code
#pragma warning(push, 0)
#include "tinyxml2.h"
// TODO [lpavic]: write comment why is this pragma added to code
#pragma warning(pop)
#include "BrickType.h"

class Level
{
private:
	unsigned int rowCount;
	unsigned int columnCount;
	unsigned int rowSpacing;
	unsigned int columnSpacing;
	std::string backgroundTexture; // this is image of board // TODO [lpavic]: this variable is unused (load unique image (.dds file) (instead of making path inside program))
	BrickType brickType[5];
	std::string bricks;

	unsigned int numOfBricks;
	std::vector<BrickType> blockOfBricks; // TODO [lpavic]: this should be done with array instead of vector (vector uses much more memory)
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