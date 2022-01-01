#pragma once

#include "tinyxml2.h"
#include <iostream>

class BrickType
{
private:
	std::string ID;
	std::string texture;
	std::string hitPoints; // TODO [lpavic]: impenetrable brick's HP is Infinite
	std::string hitSound;
	std::string breakSound; // TODO [lpavic]: impenetrable brick hasn't got this attribute, see how to not use this attribute
	unsigned int breakScore; // TODO [lpavic]: impenetrable brick hasn't got this attribute, see how to not use this attribute
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

	BrickType& operator =(BrickType&& temp);
	/**/
	BrickType& operator = (const BrickType&) = default;
	/**/
};