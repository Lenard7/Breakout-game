#include "Brick.h"
#include "Resources.h"


Brick::Brick(const tinyxml2::XMLElement& Brick) : GameElement()
{
		this->ID = Brick.Attribute("Id");
		this->texture_path = std::string(Resources::path_resources) + std::string(Brick.Attribute("Texture"));
		this->hit_points = Brick.Attribute("HitPoints");
		// TODO [lpavic]: make this hitsound path correct
		this->hit_sound = Brick.Attribute("HitSound");

		if (this->ID != "I")
		{
			// TODO [lpavic]: make this breaksound path correct
			this->break_sound = Brick.Attribute("BreakSound");
			this->break_score = Brick.UnsignedAttribute("BreakScore");
		}
}


 Brick& Brick::operator =(Brick&& temp)
 {
 	if (this != &temp)
 	{
		GameElement::operator=(std::move(temp));
 		this->ID = temp.ID;
 		this->texture_path = temp.texture_path;
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


const unsigned& Brick::getBreakScore() const { return this->break_score; }
const std::string& Brick::getBreakSound() const { return this->break_sound; }
const std::string& Brick::getHitPoints() const { return this->hit_points; }
const std::string& Brick::getHitSound() const { return this->hit_sound; }
const bool& Brick::getIsAlive() const { return this->is_alive; }

void Brick::setHitPoints(const std::string hit_points) { this->hit_points = hit_points; }
void Brick::setIsAlive(const bool is_alive) {this->is_alive = is_alive; }
