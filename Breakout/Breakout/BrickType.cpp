#include "BrickType.h"


BrickType::BrickType() : breakScore(0) {}


BrickType::BrickType(tinyxml2::XMLElement* brickType)
{
	
		this->ID = brickType->Attribute("Id"); // declare this->ID as std::string

		this->texture = brickType->Attribute("Texture");

		this->hitPoints = brickType->Attribute("HitPoints");

		this->hitSound = brickType->Attribute("HitSound");

		if (this->ID != "I")
		{
			this->breakSound = brickType->Attribute("BreakSound");
			this->breakScore = brickType->UnsignedAttribute("BreakScore");
		}

}


BrickType::~BrickType() {}


std::string BrickType::getTexture() { return this->texture; }
std::string BrickType::getHitPoints() { return this->hitPoints; }
std::string BrickType::getHitSound() { return this->hitSound; }
std::string BrickType::getBreakSound() { return this->breakSound; }
unsigned int BrickType::getBreakScore() { return this->breakScore; }
std::string BrickType::getID() { return this->ID; }

void BrickType::setID(std::string ID) { this->ID = ID; }
void BrickType::setHitPoints(std::string hitPoints) { this->hitPoints = hitPoints; }

/**/
BrickType::BrickType(BrickType&&) {}
/**/

BrickType& BrickType::operator =(BrickType&& temp)
{
	this->ID = temp.ID;
	this->texture = temp.texture;
	this->hitPoints = temp.hitPoints;
	this->hitSound = temp.hitSound;
	if (temp.ID != "I")
	{
		this->breakSound = temp.breakSound;
		this->breakScore = temp.breakScore;
	}
	return *this;
}