#include "Brick.h"
#include "ErrorHandler.h"
#include "Resources.h"


Brick::Brick(const tinyxml2::XMLElement& Brick) : GameElement()
{
	const char* temp;

	// TODO [lpavic]: maybe implement function that loads attributes safely (code is repeating)
	// QueryStringAttribute function not used because this->ID is std::string data type, not const char*
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

		if (Brick.QueryUnsignedAttribute("BreakScore", &(this->break_score)) != tinyxml2::XML_SUCCESS)
		{
			THROW_FAILURE("Error while parsing \"BreakScore\" attribute from xml file!\n");
		}
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
