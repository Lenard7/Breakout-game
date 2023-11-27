#include "BrickType.h"


BrickType::BrickType() : break_score(0) {}


BrickType::BrickType(const tinyxml2::XMLElement& brickType)
{
	
		this->ID = brickType.Attribute("Id");
		this->texture = brickType.Attribute("Texture");
		this->hit_points = brickType.Attribute("HitPoints");
		this->hit_sound = brickType.Attribute("HitSound");

		if (this->ID != "I")
		{
			this->break_sound = brickType.Attribute("BreakSound");
			this->break_score = brickType.UnsignedAttribute("BreakScore");
		}

}


 BrickType& BrickType::operator =(BrickType&& temp)
 {
 	if (this != &temp)
 	{
 		this->ID = temp.ID;
 		this->texture = temp.texture;
 		this->hit_points = temp.hit_points;
 		this->hit_sound = temp.hit_sound;

		if (temp.ID != "I")
		{
			this->break_sound = temp.break_sound;
			this->break_score = temp.break_score;
		}
	}
	return *this;
}


const std::string& BrickType::getTexture() const { return this->texture; }
const std::string& BrickType::getHitPoints() const { return this->hit_points; }
const std::string& BrickType::getHitSound() const { return this->hit_sound; }
const std::string& BrickType::getBreakSound() const { return this->break_sound; }
const unsigned& BrickType::getBreakScore() const { return this->break_score; }
const std::string& BrickType::getID() const { return this->ID; }
void BrickType::setID(const std::string ID) { this->ID = ID; }
void BrickType::setHitPoints(const std::string hit_points) { this->hit_points = hit_points; }

