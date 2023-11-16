#include "BrickType.h"


BrickType::BrickType() : breakScore(0) {}


BrickType::BrickType(const tinyxml2::XMLElement& brickType)
{
	
		this->ID = brickType.Attribute("Id");
		this->texture = brickType.Attribute("Texture");
		this->hitPoints = brickType.Attribute("HitPoints");
		this->hitSound = brickType.Attribute("HitSound");

		if (this->ID != "I")
		{
			this->breakSound = brickType.Attribute("BreakSound");
			this->breakScore = brickType.UnsignedAttribute("BreakScore");
		}

}


 BrickType& BrickType::operator =(BrickType&& temp)
 {
 	if (this != &temp)
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
	}
	return *this;
}


const std::string& BrickType::getTexture() const { return this->texture; }
const std::string& BrickType::getHitPoints() const { return this->hitPoints; }
const std::string& BrickType::getHitSound() const { return this->hitSound; }
const std::string& BrickType::getBreakSound() const { return this->breakSound; }
const unsigned& BrickType::getBreakScore() const { return this->breakScore; }
const std::string& BrickType::getID() const { return this->ID; }
void BrickType::setID(const std::string ID) { this->ID = ID; }
void BrickType::setHitPoints(const std::string hitPoints) { this->hitPoints = hitPoints; }

