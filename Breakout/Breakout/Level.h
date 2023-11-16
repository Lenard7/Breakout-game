#pragma once

#include <vector>

#include "tinyxml2.h"
#include "BrickType.h"

class Level
{
private:
	unsigned rowCount;
	unsigned columnCount;
	unsigned rowSpacing;
	unsigned columnSpacing;
	// this is image of board // TODO [lpavic]: this variable is unused (load unique image (.dds file) (instead of making path inside program))
	std::string backgroundTexture;
	BrickType brickType[5];
	std::string bricks;
	unsigned numOfBricks;
	// TODO [lpavic]: this should be done with array instead of vector (vector uses much more memory)
	std::vector<BrickType> blockOfBricks;

public:
	Level();
	Level(tinyxml2::XMLDocument& doc);
	Level(const Level&) = delete;
	Level& operator =(const Level&) = delete;
	~Level();

	// TODO [lpavic]: if this function is only called inside this class, it can be private
	void PrintLevel() const;
	
	const unsigned getRowCount() const;
	const unsigned getColumnCount() const;
	const unsigned getRowSpacing() const;
	const unsigned getColumnSpacing() const;
	const std::string getBackgroundTexture() const;
	const unsigned getNumOfBricks() const;
	const std::vector<BrickType> getBlockOfBricks() const;
	// this cannot be const function nor this function cannot return const 
	// reference since it is returning the reference - this value, because it 
	// is returning the reference, can be modified
	std::vector<BrickType>& getPointerToBlockOfBricks(); 
};