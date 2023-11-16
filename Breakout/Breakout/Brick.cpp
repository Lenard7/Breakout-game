#include "Brick.h"
#include "Resources.h"


Brick::Brick(const tinyxml2::XMLElement& Brick) : GameElement()
{
		this->ID = Brick.Attribute("Id");
		this->texture_path = std::string(Resources::path_resources) + std::string(Brick.Attribute("Texture"));
		this->hitPoints = Brick.Attribute("HitPoints");
		// TODO [lpavic]: make this hitsound path correct
		this->hitSound = Brick.Attribute("HitSound");

		if (this->ID != "I")
		{
			// TODO [lpavic]: make this breaksound path correct
			this->breakSound = Brick.Attribute("BreakSound");
			this->breakScore = Brick.UnsignedAttribute("BreakScore");
		}
}


 Brick& Brick::operator =(Brick&& temp)
 {
 	if (this != &temp)
 	{
		GameElement::operator=(std::move(temp));
 		this->ID = temp.ID;
 		this->texture_path = temp.texture_path;
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


const unsigned& Brick::getBreakScore() const { return this->breakScore; }
const std::string& Brick::getBreakSound() const { return this->breakSound; }
const std::string& Brick::getHitPoints() const { return this->hitPoints; }
const std::string& Brick::getHitSound() const { return this->hitSound; }
const bool& Brick::getIsAlive() const { return this->is_alive; }

void Brick::setHitPoints(const std::string hitPoints) { this->hitPoints = hitPoints; }
void Brick::setIsAlive(const bool is_alive) {this->is_alive = is_alive; }
