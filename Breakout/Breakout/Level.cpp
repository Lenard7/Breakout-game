#include "Level.h"
#include "BrickType.h"

#include <string>

Level::Level() : columnCount(0), 
	columnSpacing(0), 
	numOfBricks(0), 
	rowCount(0), 
	rowSpacing(0) 
{}
/*
// default constructor
complx() : re(0), im(0) { }

rowCount;
	unsigned int columnCount;
	unsigned int rowSpacing;
	unsigned int columnSpacing;
	std::string backgroundTexture;
	BrickType brickType[5];
	std::string bricks;

	unsigned int numOfBricks;
	std::vector<BrickType> blockOfBricks;

*/
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

	tinyxml2::XMLElement* brickTypes = rootElement->FirstChildElement("BrickTypes");
	if (brickTypes == NULL)
	{
		throw;
	}
	tinyxml2::XMLElement* brickType = brickTypes->FirstChildElement("BrickType");

	unsigned int j = 0;
	while (brickType)
	{
		BrickType brickTypeObject(brickType);
		this->brickType[j] = brickTypeObject;
		brickType = brickType->NextSiblingElement("BrickType");
		j++;
	}

	this->brickType[4].setID("_"); // TODO [lpavic]: this hardcoded 4 should be variable depending how many brickTypes are there

	PrintLevel();

	tinyxml2::XMLElement* bricks = rootElement->FirstChildElement("Bricks");
	if (brickTypes == NULL)
	{
		throw;
	}
	this->bricks = bricks->GetText();
	std::cout << "bricks string: " << this->bricks << "\n"; // printing bricks string

	this->numOfBricks = this->rowCount * this->columnCount; // empty spaces are special kind of bricks which are not going to be drawn and their HP = 0;

	const int tempNumOfBricks = this->numOfBricks;
	int tempBrickCount = 0;
	for (unsigned int sizeOfBricksString = 0; sizeOfBricksString < static_cast<unsigned int>(this->bricks.size()) && tempBrickCount < static_cast<int>(this->numOfBricks); sizeOfBricksString++)
	{
		switch (this->bricks[sizeOfBricksString])
		{
			case 'S':
				for (unsigned j = 0; j < 5; j++) // TODO [lpavic]: hardcoded 5 types of bricktypes, this should be variable, not const
				{
					if (this->brickType[j].getID() == "S")
					{
						this->blockOfBricks.push_back(this->brickType[j]);
						tempBrickCount++;
					}
				}
				break;

			case 'M':
				for (unsigned j = 0; j < 5; j++) // TODO [lpavic]: hardcoded 5 types of bricktypes, this should be variable, not const
				{
					if (this->brickType[j].getID() == "M")
					{
						this->blockOfBricks.push_back(this->brickType[j]);
						tempBrickCount++;
					}
				}
				break;

			case 'H':
				for (unsigned j = 0; j < 5; j++) // TODO [lpavic]: hardcoded 5 types of bricktypes, this should be variable, not const
				{
					if (this->brickType[j].getID() == "H")
					{
						this->blockOfBricks.push_back(this->brickType[j]);
						tempBrickCount++;
					}
				}
				break;

			case 'I':
				for (unsigned j = 0; j < 5; j++) // TODO [lpavic]: hardcoded 5 types of bricktypes, this should be variable, not const
				{
					if (this->brickType[j].getID() == "I")
					{
						this->blockOfBricks.push_back(this->brickType[j]);
						tempBrickCount++;
					}
				}
				break;

			case '_':
				for (unsigned j = 0; j < 5; j++) // TODO [lpavic]: hardcoded 5 types of bricktypes, this should be variable, not const
				{
					if (this->brickType[j].getID() == "_")
					{
						this->blockOfBricks.push_back(this->brickType[j]);
						tempBrickCount++;
					}
				}
				break;

			default:
				break;
		}
	}
}


void Level::PrintLevel() // TODO [lpavic]: finish printing all attributes of class Level
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

/*Inline functions*/
unsigned int Level::getRowCount()
{
	return this->rowCount;
}


unsigned int Level::getColumnCount()
{
	return this->columnCount;
}


unsigned int Level::getRowSpacing()
{
	return this->rowSpacing;
}


unsigned int Level::getColumnSpacing()
{
	return this->columnSpacing;
}


std::string Level::getBackgroundTexture()
{
	return this->backgroundTexture;
}


unsigned int Level::getNumOfBricks()
{
	return this->numOfBricks;
}


std::vector<BrickType> Level::getBlockOfBricks()
{
	return this->blockOfBricks;
}


std::vector<BrickType>& Level::getPointerToBlockOfBricks()
{
	return this->blockOfBricks;
}