#include "Level.h"
#include "BrickType.h"

#include <string>

Level::Level() 
{
	
}


Level::Level(tinyxml2::XMLDocument & doc)
{
	tinyxml2::XMLElement* rootElement = doc.FirstChildElement("Level");
	if (rootElement == NULL)
	{
		throw;
	}	
	this->rowCount = rootElement->UnsignedAttribute("RowCount");
	this->columnCount = rootElement->UnsignedAttribute("ColumnCount");
	this->rowSpacing = rootElement->UnsignedAttribute("RowSpacing");
	this->columnSpacing = rootElement->UnsignedAttribute("ColumnSpacing");
	this->backgroundTexture = rootElement->Attribute("BackgroundTexture");

	//this->brickType = new BrickType[4]; // hardcored 4: there are 4 types of bricks

	tinyxml2::XMLElement* brickTypes = rootElement->FirstChildElement("BrickTypes");
	if (brickTypes == NULL)
	{
		throw;
	}
	tinyxml2::XMLElement* brickType = brickTypes->FirstChildElement("BrickType");

	unsigned int j = 0;
	while (brickType) //bricktype must be array of objects
	{
		BrickType brickTypeObject(brickType);
		this->brickType[j] = brickTypeObject; // TODO [lpavic]: move with assign = operator
		brickType = brickType->NextSiblingElement("BrickType");
		j++;
	}

	PrintLevel(); // test purpose only
	// TODO [lpavic]: implement reading Bricks string
}


void Level::PrintLevel() // test purpose only
{
	std::cout << this->rowCount << "\n"
		<< this->columnCount << "\n"
		<< this->rowSpacing << "\n"
		<< this->columnSpacing << "\n"
		<< this->backgroundTexture << "\n\n";

	BrickType* temp = this->brickType;
	for (unsigned int j = 0; j < 4; j++) // TODO [lpavic]: this hardcoded 4 should be variable depending how many brickTypes are there
	{
		std::cout << (temp + j)->getID() << "\n"
			<< (temp + j)->getTexture() << "\n"
			<< (temp + j)->getHitPoints() << "\n"
			<< (temp + j)->getHitSound() << "\n";
		if ((temp + j)->getID() != "I")
		{
			std::cout << (temp + j)->getBreakSound() << "\n"
				<< (temp + j)->getBreakScore() << "\n";
		}
	}
}


Level::~Level() 
{
	//delete[] this->brickType;
}