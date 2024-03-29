#include "Brick.h"
#include "ErrorHandler.h"
#include "Resources.h"


Brick::Brick(const tinyxml2::XMLElement& brick) : GameElement()
{
	const char* temp;

	// TODO [lpavic]: maybe implement function that loads attributes safely (code is repeating)
	// QueryStringAttribute function not used because this->ID is std::string data type, not const char*
	temp = brick.Attribute("Id");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"id\" attribute from xml file!\n");
	}
	this->ID = std::string(temp);
	
	temp = brick.Attribute("Texture");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"Texture\" attribute from xml file!\n");
	}
	this->texture_path = std::string(Resources::path_resources) + std::string(temp);

	temp = brick.Attribute("HitPoints");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"HitPoints\" attribute from xml file!\n");
	}
	this->hit_points = temp;

	// TODO [lpavic]: make this hitsound path correct
	temp = brick.Attribute("HitSound");
	if (temp == nullptr)
	{
		THROW_FAILURE("Error while parsing \"HitSound\" attribute from xml file!\n");
	}
	this->hit_sound = temp;

	if (this->ID != "I")
	{
		// TODO [lpavic]: make this breaksound path correct
		temp = brick.Attribute("BreakSound");
		if (temp == nullptr)
		{
			THROW_FAILURE("Error while parsing \"BreakSound\" attribute from xml file!\n");
		}
		this->break_sound = temp;

		if (brick.QueryUnsignedAttribute("BreakScore", &(this->break_score)) != tinyxml2::XML_SUCCESS)
		{
			THROW_FAILURE("Error while parsing \"BreakScore\" attribute from xml file!\n");
		}
	}
	else
	{
		this->break_sound = "";
		this->break_score = 0;
	}
}
