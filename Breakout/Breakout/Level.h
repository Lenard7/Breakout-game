#pragma once

#include <iostream>

#include "tinyxml2.h"
#include "BrickType.h"

class Level
{
private:
	unsigned int rowCount;
	unsigned int columnCount;
	unsigned int rowSpacing;
	unsigned int columnSpacing;
	std::string backgroundTexture;
	// TODO [lpavic]: add array of BrickTypes here as Bricktype* or as vector of Bricktype
	BrickType brickType[4];
	std::string bricks;
public:
	Level();
	Level(tinyxml2::XMLDocument& doc);
	~Level();

	void PrintLevel();

	
};