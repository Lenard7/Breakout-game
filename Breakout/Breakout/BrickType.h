#pragma once

#include "tinyxml2.h"

#include <iostream>

class BrickType
{
private:
	std::string ID;
	std::string texture; // TODO [lpavic]: this variable is unused (load unique image (.dds file) (instead of making path inside program))
	std::string hitPoints;
	std::string hitSound; // TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program)) 
	std::string breakSound; // TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	unsigned int breakScore;
public:
	BrickType();
	/**/ // https://stackoverflow.com/questions/31264984/c-compiler-error-c2280-attempting-to-reference-a-deleted-function-in-visual
	BrickType(BrickType&&);
	BrickType(const BrickType&) = default;
	/**/
	BrickType(tinyxml2::XMLElement* brickType);
	~BrickType();

	std::string getTexture();
	std::string getHitPoints();
	std::string getHitSound();
	std::string getBreakSound();
	unsigned int getBreakScore();
	std::string getID();

	void setID(std::string ID);
	void setHitPoints(std::string hitPoints);

	BrickType& operator =(BrickType&& temp);
	/**/
	BrickType& operator = (const BrickType&) = default;
	/**/
};