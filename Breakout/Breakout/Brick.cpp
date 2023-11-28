#include "Brick.h"
#include "ErrorHandler.h"
#include "Resources.h"


Brick::Brick(const tinyxml2::XMLElement& Brick) : GameElement()
{
	const char* temp;

	// TODO [lpavic]: maybe implement function that loads attributes safely (code is repeating)
	temp = Brick.Attribute("Id");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"id\" attribute from xml file!\n");
	}
	this->ID = std::string(temp);
	
	temp = Brick.Attribute("Texture");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"Texture\" attribute from xml file!\n");
	}
	this->texture_path = std::string(Resources::path_resources) + std::string(temp);

	temp = Brick.Attribute("HitPoints");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"HitPoints\" attribute from xml file!\n");
	}
	this->hit_points = temp;

	// TODO [lpavic]: make this hitsound path correct
	temp = Brick.Attribute("HitSound");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"HitSound\" attribute from xml file!\n");
	}
	this->hit_sound = temp;

	if (this->ID != "I")
	{
		// TODO [lpavic]: make this breaksound path correct
		temp = Brick.Attribute("BreakSound");
		if (temp == nullptr)
		{
			THROW_FAILURE("Error while parsing \"BreakSound\" attribute from xml file!\n");
		}
		this->break_sound = temp;

		// TODO [lpavic]: se how to check error here, maybe use Attribute method instead UnsignedAttribute?
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
